#pragma once

#include "RenderContext.hpp"
#include "Window.fpp"
#include "../config/BaseProxy.hpp"
#include "../input/InputEvent.hpp"
#include "../input/WindowEvent.hpp"
#include "../util/VectorCore.hpp"

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

struct GLFWwindow;

namespace lumina {

enum class CursorMode : uint8_t {
  Normal, Hidden, Free
};


class Window : public config::CommonBase {
public:
  Window(std::string title = "Lumina Application",
         Vec2i size = Vec2i(600, 400));
  ~Window();

  using EventCallback = std::function<EventResult(InputEvent)>;
  using EventCallbackIndex = std::vector<EventCallback>::size_type;

  using WindowCallback = std::function<EventResult(WindowEvent)>;
  using WindowCallbackIndex = std::vector<WindowCallback>::size_type;

  void setTitle(std::string title);
  void setVersionHint(int major, int minor = 0);
  void setVSync(bool enable);
  void setCursorMode(CursorMode mode);
  void resize(Vec2i size);
  Vec2i getSize();
  RenderContext& getRenderContext();
  void open();
  void close();
  void pollEvents();
  void update();
  bool isValid();

  EventCallbackIndex addEventCallback(EventCallback&& callback);
  void removeEventCallback(EventCallbackIndex index);

  WindowCallbackIndex addWindowCallback(WindowCallback&& callback);
  void removeWindowCallback(WindowCallbackIndex index);

private:
  GLFWwindow* m_window;
  Vec2i m_size;
  std::pair<std::int16_t, std::int16_t> m_version;
  std::string m_title;  // TODO: check if we need this
  std::unique_ptr<RenderContext> m_renderContext;
  std::vector<InputEvent> m_eventQueue;
  std::vector<EventCallback> m_eventCallbacks;
  std::vector<WindowEvent> m_windowEventQueue;
  std::vector<WindowCallback> m_windowCallbacks;
  float m_lastMouseX, m_lastMouseY;
  bool m_resetLastPos;
  CursorMode m_cursorMode;


  void postEvent(InputEvent e);
  void postWindowEvent(WindowEvent e);

  static std::map<GLFWwindow*, Window*> s_eventReceiver;

  static void resizeCallback(GLFWwindow* win, int width, int height);
  static void keyCallback(GLFWwindow* win,
                          int key,
                          int scancode,
                          int action,
                          int mods);
  static void charCallback(GLFWwindow* win, unsigned int key);
  static void mouseButtonCallback(GLFWwindow* win,
                                  int button,
                                  int action,
                                  int mods);
  static void mousePosCallback(GLFWwindow* w, double xpos, double ypos);
  static void mouseScrollCallback(GLFWwindow* w, double x, double y);
  static void windowCloseCallback(GLFWwindow* w);
};

}

#include "Window.tpp"
