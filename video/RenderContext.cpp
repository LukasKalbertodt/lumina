#include "GLException.hpp"
#include "GLTools.hpp"
#include "Program.hpp"
#include "HotRenderContext.hpp"
#include "RenderContext.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lumina {

bool RenderContext::s_contextPresent = false;


void RenderContext::create() {
  if(s_contextPresent) {
    logThrowGL("[RenderContext] You cannot create a RenderContext while "
               "another is primed!");
  }

  // context needs to be current to call glewInit
  makeCurrent();

  // glewExperimental to use context versions above 3.2
  glewExperimental = GL_TRUE;
  GLenum status = glewInit();

  // check for errors
  if(status != GLEW_OK) {
    logError("[RenderContext] glewInit() failed with status <", status, ">!");
    throw GLException("glewInit() failed");
  }

  // check for GL error (glew often causes one when using new context versions)
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logNotice("[RenderContext] glewInit() caused an openGL error <",
              translateGLError(err), ">.");
  }

  // reset state
  resetCurrent();
}

void RenderContext::makeCurrent() {
  glfwMakeContextCurrent(m_windowHandle);
  s_contextPresent = true;
}

void RenderContext::resetCurrent() {
  glfwMakeContextCurrent(0);
  s_contextPresent = false;
}

void RenderContext::prime(std::function<void(HotRenderContext&)> func) {
  // check if another target is already current
  if(s_contextPresent) {
    logThrowGL("[RenderContext] You cannot prime more than one RenderContext "
               "at a time!");
  }

  makeCurrent();
  HotRenderContext hot(*this);
  func(hot);
  resetCurrent();
}

// void RenderContext::execute(Program& prog,
//                             std::function<void(HotProgram&)> func) {
// }


} // namespace lumina