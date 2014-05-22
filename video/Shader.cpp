#include "Shader.hpp"
#include "GLException.hpp"  

#include <vector>
using namespace std;

namespace lumina {

template <ShaderType Type>
Shader<Type>::~Shader() {
  // glDeleteShader will do nothing if m_handle is 0
  glDeleteShader(m_handle);
}

template <>
void Shader<ShaderType::Vertex>::createShaderObject() {
  m_handle = glCreateShader(GL_VERTEX_SHADER);
}

template <>
void Shader<ShaderType::Fragment>::createShaderObject() {
  m_handle = glCreateShader(GL_FRAGMENT_SHADER);
}

template <ShaderType Type>
void Shader<Type>::compile(ShaderSource source) {
  // assign filename
  m_filename = source.filename;

  // create shader object
  createShaderObject();

  // set shader source code
  const char *str = source.code.data();
  const int lenght = source.code.size();
  glShaderSource(m_handle, 1, &str, &lenght);

  glCompileShader(m_handle);

  // check for errors
  GLint compileStatus;
  glGetShaderiv(m_handle, GL_COMPILE_STATUS, &compileStatus);
  if(compileStatus != GL_TRUE) {
    GLint logLength;
    glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &logLength);
    vector<char> compileLog(logLength);
    glGetShaderInfoLog(m_handle, logLength, nullptr, compileLog.data());
    logError("[Shader] Could not compile shader <", m_filename, "> ->");
    logError("[Shader] ", compileLog.data());
    throw GLException("Could not compile shader");
  }

  log("[Shader] Shader <", m_filename, "> was successfully compiled.");
}

template <>
void Shader<ShaderType::Fragment>::compile(string source) {
}



// explicit instantiation
template class Shader<ShaderType::Vertex>;
template class Shader<ShaderType::Fragment>;

} // namespace lumina