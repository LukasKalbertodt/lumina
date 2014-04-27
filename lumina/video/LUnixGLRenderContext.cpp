#include "LUnixGLRenderContext.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lumina {

void LUnixGLRenderContext::create() {
  glewInit();
}

void LUnixGLRenderContext::makeCurrent() {
  glfwMakeContextCurrent(m_windowHandle);
}

void LUnixGLRenderContext::swapBuffer() {
  glfwSwapBuffers(m_windowHandle);
}

} // namespace lumina