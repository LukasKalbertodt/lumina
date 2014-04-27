#pragma once

#include "../config/BaseProxy.hpp"
#include "LRenderContext.hpp"

struct GLFWwindow;

namespace lumina {

class LUnixGLRenderContext : public LRenderContext, public config::CommonBase {
public:
  LUnixGLRenderContext(GLFWwindow* window) 
    : m_windowHandle(window) {
  }

  void create();
  void makeCurrent();
  void swapBuffer();

private:
  GLFWwindow* m_windowHandle;
};

}