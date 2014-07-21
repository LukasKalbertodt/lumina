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
    logThrowGL("[RenderContext] glewInit() failed with status <", status, ">!");
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

  // make context current and create HotContext
  makeCurrent();
  HotRenderContext hot(*this);

  // call function
  func(hot);

  // reset state
  resetCurrent();
}

} // namespace lumina