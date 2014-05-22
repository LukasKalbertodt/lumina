#include "LShader.hpp"
#include "GLException.hpp"  

#include <vector>
using namespace std;

namespace lumina {

template <LShaderType Type>
LShader<Type>::~LShader() {
  // glDeleteShader will do nothing if m_handle is 0
  glDeleteShader(m_handle);
}

template <>
void LShader<LShaderType::Vertex>::createShaderObject() {
  m_handle = glCreateShader(GL_VERTEX_SHADER);
}

template <>
void LShader<LShaderType::Fragment>::createShaderObject() {
  m_handle = glCreateShader(GL_FRAGMENT_SHADER);
}

template <LShaderType Type>
void LShader<Type>::compile(LShaderSource source) {
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
    logError("[LShader] Could not compile shader <", m_filename, "> ->");
    logError("[LShader] ", compileLog.data());
    throw GLException("Could not compile shader");
  }

  log("[LShader] Shader <", m_filename, "> was successfully compiled.");
}

template <>
void LShader<LShaderType::Fragment>::compile(string source) {
}



// explicit instantiation
template class LShader<LShaderType::Vertex>;
template class LShader<LShaderType::Fragment>;

} // namespace lumina