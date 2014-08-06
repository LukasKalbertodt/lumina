#include "ShaderSource.hpp"
#include "../core/LuminaException.hpp"
#include "../service/StaticLogger.hpp"

#include <fstream>
using namespace std;

namespace lumina {

ShaderSource loadShaderFromFile(std::string filename) {
  ShaderSource out;
  out.filename = filename;

  // open file and test if it can be opened
  ifstream file(filename.c_str());
  if(!file) {
    slogAndThrow<IOEx>("[ShaderSource] Could not open file<", filename, ">!");
  }

  // read file contents
  out.code.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
  
  return out;
}

}