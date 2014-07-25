#include "GLException.hpp"
#include "GLTools.hpp"
#include "Program.hpp"
#include "HotRenderContext.hpp"
#include "RenderContext.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lumina {

HotRenderContext* RenderContext::s_primedContext = nullptr;
bool RenderContext::s_creationLock = false;

void RenderContext::create() {
  if(s_primedContext || s_creationLock) {
    logThrowGL("[RenderContext] You cannot create a RenderContext while "
               "another is primed or being created!");
  }
  s_creationLock = true;

  // context needs to be current to call glewInit
  makeCurrent();

  // glewExperimental to use context versions above 3.2
  // TODO: call glewInit just once (???)
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
  s_creationLock = false;
  m_wasCreated = true;
}

void RenderContext::makeCurrent() {
  glfwMakeContextCurrent(m_windowHandle);
}

void RenderContext::resetCurrent() {
  glfwMakeContextCurrent(0);
}

void RenderContext::prime(std::function<void(HotRenderContext&)> func) {
  // check if another target is already current
  if(s_primedContext) {
    logThrowGL("[RenderContext] You cannot prime more than one RenderContext "
               "at a time!");
  }
  if(s_creationLock) {
    logThrowGL("[RenderContext] You cannot prime a RenderContext while another "
               "is being create!");
  }
  if(!m_wasCreated) {
    logThrowGL("[RenderContext] You cannot prime a RenderContext that was not "
               "created yet!");
  }

  // make context current and create HotContext
  makeCurrent();
  HotRenderContext hot(*this);
  s_primedContext = &hot;

  // call function
  func(hot);

  // reset state
  resetCurrent();
  s_primedContext = nullptr;
}

} // namespace lumina