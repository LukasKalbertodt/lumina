#include "LGLTools.hpp"
#include "Program.hpp"
#include "RenderContext.hpp"
#include "../core/LGLException.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lumina {

void RenderContext::create() {
  // glewExperimental to use context versions above 3.2
  glewExperimental = GL_TRUE;
  GLenum status = glewInit();

  // check for errors
  if(status != GLEW_OK) {
    logError("[RenderContext] glewInit() failed with status <", status, ">!");
    throw LGLException("glewInit() failed");
  }

  // check for GL error (glew often causes one when using new context versions)
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logWarning("[RenderContext] glewInit() caused an openGL error <",
               translateGLError(err),
               ">.");
  }
}

void RenderContext::makeCurrent() {
  glfwMakeContextCurrent(m_windowHandle);
}

void RenderContext::swapBuffer() {
  glfwSwapBuffers(m_windowHandle);
}

void RenderContext::execute(Program& prog,
                            std::function<void(HotProgram&)> func) {
  HotProgram hot(prog);
  func(hot);
}


} // namespace lumina