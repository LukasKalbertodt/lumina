#include "ImageJPEG.hpp"
#include "Image.hpp"
#include "../service/StaticLogger.hpp"
#include "../core/LuminaException.hpp"
#include "../util/VectorCore.hpp"
#include <jpeglib.h>
#include <fstream>
#include <vector>

namespace lumina {

// parameter
constexpr size_t bufferSize = 4096;




// =============================================================================
// Helper functions and struct for reading
// =============================================================================
// custom JPEG read functions
struct jpeg_read_stream {
  jpeg_source_mgr pub;
  JOCTET* buffer;
  std::istream* stream;
};

void init_source(j_decompress_ptr cinfo) {
  // Initialize jpeg_source_mgr
  jpeg_read_stream* src = reinterpret_cast<jpeg_read_stream*>(cinfo->src);
  src->pub.next_input_byte = nullptr;
  src->pub.bytes_in_buffer = 0;
}

boolean fill_input_buffer(j_decompress_ptr cinfo) {
  // Read data from input stream
  jpeg_read_stream* src = reinterpret_cast<jpeg_read_stream*>(cinfo->src);
  src->stream->read(reinterpret_cast<char*>(src->buffer), bufferSize);
  src->pub.next_input_byte = src->buffer;
  src->pub.bytes_in_buffer = static_cast<size_t>(src->stream->gcount());
  return TRUE;
}

void skip_input_data(j_decompress_ptr cinfo, long num_bytes_l) {
  jpeg_source_mgr* src = cinfo->src;
  size_t num_bytes = num_bytes_l;
  if(num_bytes > 0) {
    while(num_bytes > src->bytes_in_buffer) {
      num_bytes -= src->bytes_in_buffer;
      src->fill_input_buffer(cinfo);
    }
    src->next_input_byte += num_bytes;
    src->bytes_in_buffer -= num_bytes;
  }
}

void term_source(j_decompress_ptr cinfo) {}

// // Custom JPEG write functions
// struct jpeg_write_stream
// {
//   jpeg_destination_mgr pub;
//   JOCTET* buffer;
//   std::ostream* stream;
// };

// void init_destination(j_compress_ptr cinfo)
// {
//   // Initialize jpeg_destination_mgr
//   jpeg_write_stream* dest = reinterpret_cast<jpeg_write_stream*>(cinfo->dest);
//   dest->pub.next_output_byte = dest->buffer;
//   dest->pub.free_in_buffer = bufferSize;
// }

// boolean empty_output_buffer(j_compress_ptr cinfo)
// {
//   // Write data to stream and reset jpeg_destination_mgr
//   jpeg_write_stream* dest = reinterpret_cast<jpeg_write_stream*>(cinfo->dest);
//   dest->stream->write(reinterpret_cast<char*>(dest->buffer), bufferSize);
//   dest->pub.next_output_byte = dest->buffer;
//   dest->pub.free_in_buffer = bufferSize;
//   return TRUE;
// }

// void term_destination(j_compress_ptr cinfo)
// {
//   // Flush remaining data
//   jpeg_write_stream* dest = reinterpret_cast<jpeg_write_stream*>(cinfo->dest);
//   dest->stream->write(reinterpret_cast<char*>(dest->buffer),
//                       bufferSize - dest->pub.free_in_buffer);
// }



// bool CImageJPEG::Save(std::ostream& stream, IImageConstPtr img)
// {
//   // Create structs
//   jpeg_compress_struct cinfo;
//   jpeg_error_mgr jerr;

//   cinfo.err = jpeg_std_error(&jerr);
//   jpeg_create_compress(&cinfo);

//   // Set custom stream writer
//   jpeg_write_stream dest;
//   std::vector<JOCTET> buffer(bufferSize);
//   dest.buffer = buffer.data();
//   dest.stream = &stream;
//   dest.pub.init_destination = init_destination;
//   dest.pub.empty_output_buffer = empty_output_buffer;
//   dest.pub.term_destination = term_destination;
//   cinfo.dest = reinterpret_cast<jpeg_destination_mgr*>(&dest);

//   // Check image format
//   if(img->GetFormat() != SF_R8G8B8)
//     img = img->Copy()->Convert(SF_R8G8B8);

//   // Write header
//   Dim2i dim = img->GetDimension();
//   cinfo.image_width = dim.width;
//   cinfo.image_height = dim.height;
//   cinfo.input_components = 3;
//   cinfo.in_color_space = JCS_RGB;
//   jpeg_set_defaults(&cinfo);
//   jpeg_set_quality(&cinfo, 95, TRUE);
//   jpeg_start_compress(&cinfo, TRUE);

//   // Write image
//   size_t rowbytes = img->GetPitch();
//   JSAMPROW img_data = const_cast<JSAMPROW>(img->GetData());
//   while(cinfo.next_scanline < cinfo.image_height)
//   {
//     JSAMPROW row = img_data + cinfo.next_scanline*rowbytes;
//     jpeg_write_scanlines(&cinfo, &row, 1);
//   }

//   // Cleanup
//   jpeg_finish_compress(&cinfo);
//   jpeg_destroy_compress(&cinfo);
//   return true;
// }


// =============================================================================
// some other helper functions
// =============================================================================
static bool isJPEGFileImpl(std::istream& stream) {
  // JPEG file needs to start with those 3 bytes
  static const uint8_t magicNumber[3] = {0xFF, 0xD8, 0xFF};

  // read start of file
  char input[3];
  stream.read(input, 3);
  if(!stream.good())
    return false;
  return (memcmp(input, magicNumber, 3) == 0);
}


// =============================================================================
// Implementation of "public" functions
// =============================================================================
bool isJPEGExentsion(std::string filename) {
  auto ext = filename.substr(filename.rfind(".") + 1);
  if(ext == ".jpg" || ext == ".jpeg") {
    return true;
  }
  return false;
}

bool isJPEGFile(std::string filename) {
  // try to open file
  std::ifstream file(filename.c_str());

  // if file could not be opened... it's not a JPEG file (?)
  if(!file) {
    slogWarning("[isJPEGFile] Unable to open file<", filename, ">!");
    return false;
  }

  return isJPEGFileImpl(file);
}

ImageBox loadJPEGImage(std::string filename) {
  // open file
  std::ifstream file(filename.c_str());
  if(!file) {
    slogError("[loadJPEGImage] Unable to open file<", filename, ">!");
    throw IOEx("[loadJPEGImage] Unable to open file!");
  }

  // Create structs
  jpeg_decompress_struct cinfo;
  jpeg_error_mgr jerr;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);

  // Set custom stream reader
  jpeg_read_stream src;
  std::vector<JOCTET> buffer(bufferSize);
  src.buffer = buffer.data();
  src.stream = &file;
  src.pub.init_source = init_source;
  src.pub.fill_input_buffer = fill_input_buffer;
  src.pub.skip_input_data = skip_input_data;
  src.pub.resync_to_restart = jpeg_resync_to_restart;
  src.pub.term_source = term_source;
  cinfo.src = reinterpret_cast<jpeg_source_mgr*>(&src);

  // Read header
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);
  int height = cinfo.image_height;
  int width = cinfo.image_width;

  // Check image format (has to be RGB8bit)
  int bytesPerPixel = cinfo.num_components;
  if(bytesPerPixel != 3) {
    // clean up resources
    jpeg_destroy_decompress(&cinfo);

    // log and throw
    slogError("[loadJPEGImage] Error: JPEG-file<", filename, "> has an invalid"
      " number of components/bytesPerPixel<", bytesPerPixel, "> (has to be"
      " 3)!");
    throw IOEx("[loadJPEGImage] Error: JPEG-file has an invalid number of "
      "components/bytesPerPixel");
  }

  // calculate bytes per row
  int rowbytes = bytesPerPixel*width;

  // create new image (color format is always RGB 8bit)
  Image<Color8> img;
  img.create(Vec2i(width, height));
  uint8_t* img_data = static_cast<uint8_t*>(img.data());

  // read actual data into buffer owned by image
  while(cinfo.output_scanline < cinfo.output_height) {
    uint8_t* row = img_data + cinfo.output_scanline*rowbytes;
    jpeg_read_scanlines(&cinfo, &row, 1);
  }

  // cleanup
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  return ImageBox(std::move(img));
}

}