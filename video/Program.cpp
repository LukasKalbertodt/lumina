#include "Program.hpp"
#include "GLException.hpp"

#include <vector>
using namespace std;

namespace lumina {

void Program::link(Shader<ShaderType::Vertex> vs,
                   Shader<ShaderType::Fragment> fs) {
  m_program = glCreateProgram();

  // attach both shaders
  glAttachShader(m_program, vs.getHandle());
  glAttachShader(m_program, fs.getHandle());

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
    logError("[Program] Could not link shaders <",
             vs.getFilename(),
             ", ",
             fs.getFilename(),
             "> ->");
    logError("[Program] ", compileLog.data());
    throw GLException("Could not compile shader");
  }
  log("[Program] Shaders <",
      vs.getFilename(),
      ", ",
      fs.getFilename(),
      "> were successfully linked.");
}

}