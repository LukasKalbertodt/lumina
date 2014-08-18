#pragma once
#include "GLObject.hpp"
#include "Shader.fpp"
#include "ShaderSource.hpp"
#include "../config/BaseProxy.hpp"

#include "GL/glew.h"
#include <string>

namespace lumina {

/** Represents an OpenGL Shader.
It's templated with the shader type. Currently vertex and fragment shaders are
supported. FShader and VShader are short typedefs for those. You can compile
a shader, but you need to link it within a Program to use it.
\tparam Type Type of the shader (Vertex or Fragment)
*/
template <ShaderType Type>
class Shader : public GLObject {
public:
  // typedefs and constexpr
  static constexpr ShaderType shaderType = Type;

  // default constructor
  Shader();

  // descructor
  ~Shader();

  /// Returns native OpenGL handle
  GLuint getHandle() const;

  /// Returns the filename of the shader
  std::string getFilename() const;

  /// Compiles the shader from a ShaderSource
  void compile(ShaderSource source);

  /// Compiles the shader from raw GLSL code (filename is set to unknown-file)
  void compile(std::string code);

  explicit operator bool() const;

private:
  GLuint m_handle;
  std::string m_filename;

  void createShaderObject();
};

}

#include "Shader.tpp"