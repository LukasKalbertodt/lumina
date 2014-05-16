#pragma once

#include "../config/BaseProxy.hpp"
#include "LRenderContext.hpp"

struct GLFWwindow;

namespace lumina {

class LRenderContext : public config::CommonBase {
public:
  LRenderContext(GLFWwindow* window) 
    : m_windowHandle(window) {
  }

  void create();
  void makeCurrent();
  void swapBuffer();

private:
  GLFWwindow* m_windowHandle;
};

}