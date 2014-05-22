#pragma once
#include "../config/BaseProxy.hpp"
#include "ShaderSource.hpp"

#include "GL/glew.h"
#include <string>

namespace lumina {

enum class ShaderType {
  Vertex, Fragment
};

template <ShaderType Type>
class Shader : public config::CommonBase {
public:
  // typedefs and constexpr
  static constexpr ShaderType shaderType = Type;

  // default constructor
  Shader() : m_handle(0) {}

  // descructor
  ~Shader();

  GLuint getHandle() { return m_handle; }
  std::string getFilename() { return m_filename; }

  void compile(ShaderSource source);
  void compile(std::string code) {
    compile(ShaderSource(code, "unknown-file"));
  }

private:
  GLuint m_handle;
  std::string m_filename;

  void createShaderObject();
};

}