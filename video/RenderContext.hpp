#pragma once
#include "Program.fpp"
#include "FrameBuffer.hpp"
#include "RenderContext.fpp"
#include "../config/BaseProxy.hpp"

#include <functional>

// forward declare GLFW types
struct GLFWwindow;


namespace lumina {

class RenderContext : public config::CommonBase {
public:
  RenderContext(GLFWwindow* window);

  void create();
  void makeCurrent();
  void swapBuffer();
  FrameBuffer& getDefaultFrameBuffer();

  // void execute(Program& prog, std::function<void(HotProgram&)> func);

private:
  GLFWwindow* m_windowHandle;
  FrameBuffer m_defaultFB;
};

} // namespace lumina

#include "RenderContext.tpp"