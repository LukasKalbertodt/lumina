#include "Program.hpp"
#include "HotProgram.hpp"
#include "GLException.hpp"

#include <vector>
using namespace std;

namespace lumina {

bool Program::s_isPrimed = false;

void Program::create(VShader& vs, FShader& fs) {
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
    logError("[Program] Could not link shaders <", vs.getFilename(),
             ", ", fs.getFilename(), "> ->");
    logError("[Program] ", compileLog.data());
    throw GLException("Could not link shaders");
  }
  logDebug("[Program] Shaders <", vs.getFilename(), ", ", fs.getFilename(),
           "> were successfully linked.");

  // detach shaders (TODO: is this a good idea?)
  glDetachShader(program, vs.getHandle());
  glDetachShader(program, fs.getHandle());

  // check for any error
  checkGLError("[Program] GL error while linking program <", GLERR, ">!");

  // linking was successful: commit changes
  m_handle = program;
}

void Program::prime(std::function<void(HotProgram&)> func) {
  // check if the program was created yet
  if(m_handle == 0) {
    logThrowGL("[Program] Attempt to prime program before it was created!");
  }

  // check if another program is primed
  if(s_isPrimed) {
    logThrowGL("[Program] You can only prime one Program at a time!");
  }
  s_isPrimed = true;

  // bind program and set necessary parameter
  glUseProgram(m_handle);
  primitiveProc.bindStage();
  perFragProc.bindStage();

  // create HotProgram and call function
  HotProgram hot(*this);
  func(hot);

  // reset parameter and unbind program
  perFragProc.unbindStage();
  primitiveProc.unbindStage();
  glUseProgram(0);

  // reset primed flag
  s_isPrimed = false;

  // check if any OpenGL error occured
  checkGLError("[Program] Error<", GLERR, "> while after priming Program!");
}

}