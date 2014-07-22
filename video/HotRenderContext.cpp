#include "HotRenderContext.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lumina {

void HotRenderContext::swapBuffer() {
  glfwSwapBuffers(m_cold.m_windowHandle);
}

template<>
int HotRenderContext::getProperty(GLProp prop) {
  GLint out;
  glGetIntegerv(translateGLProp(prop), &out);

  checkGLError("[HotRenderContext] Error<", GLERR, "> while executing glGet!");
  return out;
}


}