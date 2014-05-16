#include "LRenderContext.hpp"
#include "LGLTools.hpp"
#include "../core/LGLException.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace lumina {

void LRenderContext::create() {
  // glewExperimental to use context versions above 3.2
  glewExperimental = GL_TRUE;
  GLenum status = glewInit();

  // check for errors
  if(status != GLEW_OK) {
    logError("[LRenderContext] glewInit() failed!");
    throw LGLException("glewInit() failed");
  }

  // check for GL error (glew often causes one when using new context versions)
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logWarning("[LRenderContext] glewInit() caused an openGL error <",
               translateGLError(err),
               ">.");
  }
}

void LRenderContext::makeCurrent() {
  glfwMakeContextCurrent(m_windowHandle);
}

void LRenderContext::swapBuffer() {
  glfwSwapBuffers(m_windowHandle);
}

} // namespace lumina