#pragma once

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../config/BaseProxy.hpp"
#include "../core/LInputEvent.hpp"
#include "../core/LKeyCode.hpp"
#include "../util/LVector.hpp"
#include "LDriverType.hpp"
#include "LRenderContext.hpp"
#include "LUnixGLRenderContext.hpp"

struct GLFWwindow;

namespace lumina {

class LUnixWindow : public config::CommonBase {
public:
  LUnixWindow(std::string title = "Lumina Application",
              Vec2i size = Vec2i(600, 400))
    : m_window(nullptr), m_size(size), m_title(title) {}

  ~LUnixWindow();

  using EventCallback = std::function<LEventResult(const LInputEvent&)>;
  using CallbackAccessor = std::vector<EventCallback>::size_type;

  void setTitle(std::string title);
  void setVersionHint(int major, int minor = 0);
  void resize(Vec2i size);
  Vec2i getSize();
  LRenderContext* getRenderContext(LDriverType type);
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
  std::string m_title;  // TODO: check if we need this
  std::unique_ptr<LUnixGLRenderContext> m_renderContext;
  std::vector<LInputEvent> m_eventQueue;
  std::vector<EventCallback> m_eventCallbacks;

  void postEvent(LInputEvent e);

  static std::map<GLFWwindow*, LUnixWindow*> s_eventReceiver;

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