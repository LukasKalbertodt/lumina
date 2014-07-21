#include "HotRenderContext.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lumina {

void HotRenderContext::swapBuffer() {
  glfwSwapBuffers(m_cold.m_windowHandle);
}


}