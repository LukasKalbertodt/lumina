#pragma once

#include "RenderContext.hpp"
#include "Window.fpp"
#include "../config/BaseProxy.hpp"
#include "../input/InputEvent.hpp"
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

class Window : public config::CommonBase {
public:
  Window(std::string title = "Lumina Application",
         Vec2i size = Vec2i(600, 400));
  ~Window();

  using EventCallback = std::function<EventResult(const InputEvent&)>;
  using CallbackAccessor = std::vector<EventCallback>::size_type;

  void setTitle(std::string title);
  void setVersionHint(int major, int minor = 0);
  void setVSync(bool enable);
  void resize(Vec2i size);
  Vec2i getSize();
  RenderContext& getRenderContext();
  void open();
  void close();
  void pollEvents();
  void update();
  bool isValid();

  CallbackAccessor addEventCallback(EventCallback&& callback);
  void removeEventCallback(CallbackAccessor accessor);

private:
  GLFWwindow* m_window;
  Vec2i m_size;
  std::pair<std::int16_t, std::int16_t> m_version;
  std::string m_title;  // TODO: check if we need this
  std::unique_ptr<RenderContext> m_renderContext;
  std::vector<InputEvent> m_eventQueue;
  std::vector<EventCallback> m_eventCallbacks;
  float m_lastMouseX, m_lastMouseY;
  bool m_resetLastPos;
  

  void postEvent(InputEvent e);

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
  static void mousePosCallback(GLFWwindow* win, double xpos, double ypos);
};

}

#include "Window.tpp"
