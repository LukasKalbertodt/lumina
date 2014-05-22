#pragma once

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

#include "../config/BaseProxy.hpp"
#include "../input/LInputEvent.hpp"
#include "../input/LKeyCode.hpp"
#include "../util/LVector.hpp"
#include "RenderContext.hpp"

struct GLFWwindow;

namespace lumina {

class LWindow : public config::CommonBase {
public:
  LWindow(std::string title = "Lumina Application",
              Vec2i size = Vec2i(600, 400))
    : m_window(nullptr), m_size(size), m_version(1, 1), m_title(title) {}

  ~LWindow();

  using EventCallback = std::function<LEventResult(const LInputEvent&)>;
  using CallbackAccessor = std::vector<EventCallback>::size_type;

  void setTitle(std::string title);
  void setVersionHint(int major, int minor = 0) {
    m_version = std::pair<std::int16_t, std::int16_t>(major, minor);
  }
  void setVSync(bool enable);
  void resize(Vec2i size);
  Vec2i getSize();
  RenderContext* getRenderContext();
  void open();
  void close();
  void pollEvents();
  void update();
  bool isValid();

  CallbackAccessor addEventCallback(EventCallback&& callback) {
    m_eventCallbacks.push_back(std::forward<EventCallback>(callback));
    return m_eventCallbacks.size() - 1;
  }

  void removeEventCallback(CallbackAccessor accessor) {
    m_eventCallbacks[accessor] = EventCallback();
  }

private:
  GLFWwindow* m_window;
  Vec2i m_size;
  std::pair<std::int16_t, std::int16_t> m_version;
  std::string m_title;  // TODO: check if we need this
  std::unique_ptr<RenderContext> m_renderContext;
  std::vector<LInputEvent> m_eventQueue;
  std::vector<EventCallback> m_eventCallbacks;

  void postEvent(LInputEvent e);

  static std::map<GLFWwindow*, LWindow*> s_eventReceiver;

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

  static LKeyCode translateKey(int key);
};

}