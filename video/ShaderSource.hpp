#pragma once
/** 
 * \file ShaderSource.hpp
 * \brief Pair of filename and shader code
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * A ShaderSource contains a filename and the contents of that file. You should
 * use this as source for a compilation process to get more informations.
 * 
 * This file is part of the Lumina Graphic Library.
 */
#include <string>

namespace lumina {

struct ShaderSource {
  ShaderSource() = default;
  ShaderSource(std::string code, std::string filename)
    : code(code), filename(filename) {}
  
  std::string code;
  std::string filename;
};

/**
 * \brief Loads a file and returns a ShaderSource.
 * Tries to open the given file and load it's contents. It does not parse or
 * compile the code in any way.
 * 
 * \return blub
 */
ShaderSource loadShaderFromFile(std::string filename);

} // namespace lumina