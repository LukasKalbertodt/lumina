#include "LShaderSource.hpp"

#include <fstream>
using namespace std;

namespace lumina {

LShaderSource loadShaderFromFile(std::string filename) {
  LShaderSource out;
  out.filename = filename;

  ifstream file(filename.c_str());
  out.code.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
  
  return out;
}

}