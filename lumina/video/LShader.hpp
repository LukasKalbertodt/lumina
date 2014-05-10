#pragma once
#include "../config/BaseProxy.hpp"
#include "LShaderSource.hpp"

#include "GL/glew.h"
#include <string>

namespace lumina {

enum class LShaderType {
  Vertex, Fragment
};

template <LShaderType Type>
class LShader : public config::CommonBase {
public:
  // typedefs and constexpr
  static constexpr LShaderType shaderType = Type;

  // default constructor
  LShader() : m_handle(0) {}

  // descructor
  ~LShader();

  GLuint getHandle() { return m_handle; }
  std::string getFilename() { return m_filename; }

  void compile(LShaderSource source);
  void compile(std::string code) {
    compile(LShaderSource(code, "unknown-file"));
  }

private:
  GLuint m_handle;
  std::string m_filename;

  void createShaderObject();
};

}