#pragma once
#include "Program.fpp"
#include "FrameBuffer.hpp"
#include "RenderContext.fpp"
#include "HotRenderContext.fpp"
#include "GLObject.hpp"
#include "../config/BaseProxy.hpp"

#include <functional>

// forward declare GLFW types
struct GLFWwindow;


namespace lumina {

class RenderContext : public GLObject {
public:
  RenderContext(GLFWwindow* window);

  void create();
  void prime(std::function<void(HotRenderContext&)> func);


private:
  GLFWwindow* m_windowHandle;
  FrameBuffer m_defaultFB;

  static bool s_contextPresent;
  void makeCurrent();
  void resetCurrent();

  friend HotRenderContext;
};

} // namespace lumina

#include "RenderContext.tpp"