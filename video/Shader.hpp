#pragma once
#include "GLObject.hpp"
#include "Shader.fpp"
#include "ShaderSource.hpp"
#include "../config/BaseProxy.hpp"

#include "GL/glew.h"
#include <string>

namespace lumina {

template <ShaderType Type>
class Shader : public GLObject {
public:
  // typedefs and constexpr
  static constexpr ShaderType shaderType = Type;

  // default constructor
  Shader();

  // descructor
  ~Shader();

  GLuint getHandle() const;
  std::string getFilename() const;

  void compile(ShaderSource source);
  void compile(std::string code);

private:
  GLuint m_handle;
  std::string m_filename;

  void createShaderObject();
};

}

#include "Shader.tpp"