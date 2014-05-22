#include "ShaderSource.hpp"

#include <fstream>
using namespace std;

namespace lumina {

ShaderSource loadShaderFromFile(std::string filename) {
  ShaderSource out;
  out.filename = filename;

  ifstream file(filename.c_str());
  out.code.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
  
  return out;
}

}