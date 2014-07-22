#pragma once
#include "Program.fpp"
#include "FrameBuffer.hpp"
#include "RenderContext.fpp"
#include "HotRenderContext.fpp"
#include "GLException.hpp"
#include "GLObject.hpp"
#include "../service/StaticLogger.hpp"
#include "../config/BaseProxy.hpp"

#include <functional>

// forward declare GLFW types
struct GLFWwindow;


namespace lumina {

class RenderContext : public GLContextFreeObject {
public:
  RenderContext(GLFWwindow* window);

  void create();
  void prime(std::function<void(HotRenderContext&)> func);

  static HotRenderContext& getCurrentContext();
  static bool isContextCurrent();


private:
  GLFWwindow* m_windowHandle;
  FrameBuffer m_defaultFB;

  static HotRenderContext* s_primedContext;
  static bool s_creationLock;
  void makeCurrent();
  void resetCurrent();

  friend HotRenderContext;
};

} // namespace lumina

#include "RenderContext.tpp"