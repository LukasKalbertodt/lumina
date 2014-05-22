#include "Pipeline.hpp"
#include "GLException.hpp"

#include <vector>
using namespace std;

namespace lumina {

void PipelineContainer::linkShaderProgram() {
  m_program = glCreateProgram();

  // attach both shaders
  glAttachShader(m_program, m_vertexShader.getHandle());
  glAttachShader(m_program, m_fragmentShader.getHandle());

  // link program
  glLinkProgram(m_program);

  // TODO: maybe detach shaders?

  // check for errors
  GLint linkStatus;
  glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);
  if(linkStatus != GL_TRUE) {
    GLint logLength;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
    vector<char> compileLog(logLength);
    glGetShaderInfoLog(m_program, logLength, nullptr, compileLog.data());
    logError("[Shader] Could not link shaders <",
             m_vertexShader.getFilename(),
             ", ",
             m_fragmentShader.getFilename(),
             "> ->");
    logError("[Shader] ", compileLog.data());
    throw GLException("Could not compile shader");
  }
  log("[Shader] Shaders <",
      m_vertexShader.getFilename(),
      ", ",
      m_fragmentShader.getFilename(),
      "> were successfully linked.");
}

void PipelineContainer::use() {
  glUseProgram(m_program);
}

} // namespace lumina