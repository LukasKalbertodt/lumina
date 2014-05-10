#include "LUnixGLRenderContext.hpp"
#include "../core/LGLException.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace lumina {

void LUnixGLRenderContext::create() {
  glewExperimental = GL_TRUE;
  GLenum status = glewInit();
  if(status != GLEW_OK) {
    logError("[LRenderContext] glewInit() failed!");
    throw LGLException("glewInit() failed");
  }
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logWarning(
      "[LRenderContext] glewInit() caused an openGL error <", err, ">.");
  }
}

void LUnixGLRenderContext::makeCurrent() {
  glfwMakeContextCurrent(m_windowHandle);
}

void LUnixGLRenderContext::swapBuffer() {
  glfwSwapBuffers(m_windowHandle);
}

} // namespace lumina