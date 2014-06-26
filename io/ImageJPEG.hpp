#pragma once

#include "Image.fpp"
#include <string>

namespace lumina {

ImageBox loadJPEGImage(std::string filename);
bool isJPEGFile(std::string filename);
bool isJPEGExtension(std::string filename);
void saveJPEGImage(std::string filename, ImageBox img);

}