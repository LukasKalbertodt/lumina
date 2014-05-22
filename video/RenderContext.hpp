#pragma once
#include "Program.fpp"
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

  void execute(Program& prog, std::function<void(HotProgram&)> func);

private:
  GLFWwindow* m_windowHandle;
};

} // namespace lumina

#include "RenderContext.tpp"