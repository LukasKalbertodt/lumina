#include "ImagePNG.hpp"
#include "../service/StaticLogger.hpp"
#include "../core/LuminaException.hpp"
#include "../util/VectorCore.hpp"
#include <fstream>
#include <vector>
#include <png++/png.hpp>

namespace lumina {


// =============================================================================
// some other helper functions
// =============================================================================
static bool isPNGFileImpl(std::istream& stream) {
  static const uint8_t magicNumber[]
    = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};

  // read start of file
  char input[8];
  stream.read(input, 8);
  if(!stream.good())
    return false;
  return (memcmp(input, magicNumber, 8) == 0);
}


// =============================================================================
// Implementation of "public" functions
// =============================================================================
bool isPNGExentsion(std::string filename) {
  auto ext = filename.substr(filename.rfind(".") + 1);
  if(ext == ".png") {
    return true;
  }
  return false;
}

bool isPNGFile(std::string filename) {
  // try to open file
  std::ifstream file(filename.c_str());

  // if file could not be opened... it's not a PNG file (?)
  if(!file) {
    slogWarning("[isPNGFile] Unable to open file<", filename, ">!");
    return false;
  }

  return isPNGFileImpl(file);
}

ImageBox loadPNGImage(std::string filename) {
  // open file
  std::ifstream file(filename.c_str());
  if(!file) {
    slogError("[loadPNGImage] Unable to open file<", filename, ">!");
    throw IOEx("[loadPNGImage] Unable to open file!");
  }

  png::image<png::rgba_pixel> image(filename);

  Image<Color8A> out;
  out.create(Vec2i(image.get_width(), image.get_height()));
  uint8_t* outData = static_cast<uint8_t*>(out.data());


  for(int i = 0; i < image.get_height(); ++i) {
    auto rowLen = image.get_width() * sizeof(image.get_row(i)[0]);
    memcpy(outData + i * rowLen,
           image.get_row(i).data(),
           rowLen);
  }

  return ImageBox(std::move(out));
}

void savePNGImage(std::string filename, ImageBox img) {
  // try to open file
  std::ofstream file(filename.c_str());
  if(!file) {
    slogError("[savePNGImage] Unable to open file<", filename, ">!");
    throw IOEx("[savePNGImage] Unable to open file!");
  }


}

}