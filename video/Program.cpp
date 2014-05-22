#include "Program.hpp"
#include "GLException.hpp"

#include <vector>
using namespace std;

namespace lumina {

void Program::link(LShader<LShaderType::Vertex> vs,
                   LShader<LShaderType::Fragment> fs) {
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
    logError("[LShader] Could not link shaders <",
             vs.getFilename(),
             ", ",
             fs.getFilename(),
             "> ->");
    logError("[LShader] ", compileLog.data());
    throw GLException("Could not compile shader");
  }
  log("[LShader] Shaders <",
      vs.getFilename(),
      ", ",
      fs.getFilename(),
      "> were successfully linked.");
}

}