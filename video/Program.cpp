#include "Program.hpp"
#include "GLException.hpp"

#include <vector>
using namespace std;

namespace lumina {

bool HotProgram::s_isPrimed = false;


void Program::create(VShader vs, FShader fs) {
  auto program = glCreateProgram();

  // attach both shaders
  glAttachShader(program, vs.getHandle());
  glAttachShader(program, fs.getHandle());

  // link program
  glLinkProgram(program);

  // check for errors
  GLint linkStatus;
  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
  if(linkStatus != GL_TRUE) {
    // obtain error message
    GLint logLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    vector<char> compileLog(logLength);
    glGetShaderInfoLog(program, logLength, nullptr, compileLog.data());
    logError("[Program] Could not link shaders <",
             vs.getFilename(),
             ", ",
             fs.getFilename(),
             "> ->");
    logError("[Program] ", compileLog.data());
    throw GLException("Could not link shaders");
  }
  log("[Program] Shaders <",
      vs.getFilename(),
      ", ",
      fs.getFilename(),
      "> were successfully linked.");

  // detach shaders (TODO: is this a good idea?)
  glDetachShader(program, vs.getHandle());
  glDetachShader(program, fs.getHandle());

  // check for any error
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[Program] GL error while linking program <",
             translateGLError(err),
             ">!");
    throw GLException("[Program] GL error while linking program");
  }

  // linking was successful: commit changes
  m_program = program;
}

}