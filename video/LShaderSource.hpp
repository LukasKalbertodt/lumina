#pragma once

#include <string>

namespace lumina {

struct LShaderSource {
  LShaderSource() = default;
  LShaderSource(std::string code, std::string filename)
    : code(code), filename(filename) {}
  
  std::string code;
  std::string filename;
};

LShaderSource loadShaderFromFile(std::string filename);

} // namespace lumina