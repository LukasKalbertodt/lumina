#pragma once

#include "Image.hpp"
#include <string>

namespace lumina {

ImageBox loadPNGImage(std::string filename);
bool isPNGFile(std::string filename);
bool isPNGExtension(std::string filename);
void savePNGImage(std::string filename, ImageBox img);

}