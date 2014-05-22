#pragma once

#include <string>

namespace lumina {

struct ShaderSource {
  ShaderSource() = default;
  ShaderSource(std::string code, std::string filename)
    : code(code), filename(filename) {}
  
  std::string code;
  std::string filename;
};

ShaderSource loadShaderFromFile(std::string filename);

} // namespace lumina