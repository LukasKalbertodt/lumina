#include "GLFWTools.hpp"
#include "Window.hpp"
#include "VideoException.hpp"
#include "../service/StaticLogger.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

namespace lumina {

// static member: map GLFWwindow to instances of Window for event dispatch
std::map<GLFWwindow*, Window*> Window::s_eventReceiver;


Window::~Window() {
  if(m_window) {
    close();
  }
}

RenderContext& Window::getRenderContext() {
  if(!m_renderContext) {
    m_renderContext.reset(new RenderContext(m_window));
  }
  return *m_renderContext.get();
}

void Window::open() {
   // If this is the first window -> init GLFW
  if(s_eventReceiver.empty()) {
    if(!glfwInit()) {
      logError("[Window] GLFW initialization failed!");
      throw runtime_error("GLFW initialization failed");
    }
  }

  // set window hints
  if(m_version.first != 0) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_version.first);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_version.second);
  }
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create window
  m_window
      = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), nullptr, nullptr);
  if(!m_window) {
    // if this is the first window, call glfwTerminate to clean up resources
    if(s_eventReceiver.empty()) {
      glfwTerminate();
    }

    // log error and throw
    logError("[Window] GLFW window creation failed");
    throw runtime_error("GLFW window creation failed");
  }

  // check attributes
  int major = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MAJOR);
  int minor = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MINOR);
  if(major != m_version.first || minor != m_version.second) {
    logWarning("[Window] Actual version <",
               major, ".", minor,
               "> differs from version hint <",
               m_version.first, ".", m_version.second,
               ">!");
  }

  // add to list of event receiving windows
  s_eventReceiver[m_window] = this;

  // prepare event callbacks
  glfwSetWindowSizeCallback(m_window, Window::resizeCallback);
  glfwSetKeyCallback(m_window, Window::keyCallback);
  glfwSetCharCallback(m_window, Window::charCallback);
  glfwSetMouseButtonCallback(m_window, Window::mouseButtonCallback);
  glfwSetCursorPosCallback(m_window, Window::mousePosCallback);
  glfwSetScrollCallback(m_window, Window::mouseScrollCallback);

  glfwSetWindowCloseCallback(m_window, Window::windowCloseCallback);

  log("[Window] Opened new GLFW window: Success! (Handle: ", m_window, ")");
}

void Window::setVSync(bool enable) {
  glfwSwapInterval(enable ? 1 : 0);
}

void Window::setCursorMode(CursorMode mode) {
  m_cursorMode = mode;
  int value = 0;
  switch(mode) {
    case CursorMode::Normal: value = GLFW_CURSOR_NORMAL; break;
    case CursorMode::Hidden: value = GLFW_CURSOR_HIDDEN; break;
    case CursorMode::Free: value = GLFW_CURSOR_DISABLED; break;
  }
  glfwSetInputMode(m_window, GLFW_CURSOR, value);
  m_resetLastPos = true;
}


void Window::close() {
  if(m_window) {
    glfwDestroyWindow(m_window);
    s_eventReceiver.erase(m_window);
    log("[Window] Destroyed GLFW window. (Handle: ", m_window, ")");
    m_window = nullptr;

    if(s_eventReceiver.empty()) {
      glfwTerminate();
      log("[Window] Last window was destroyed, called glfwTerminate: Success!");
    }
  }
  else {
    logWarning("[Window] Attempting to close a GLFW window, "
      "which is not open!");
  }
}

void Window::setTitle(std::string title) {
  m_title = title;
  if(m_window) {
    glfwSetWindowTitle(m_window, title.c_str());
  }
}

void Window::resize(Vec2i size) {
  m_size = size;
  if(m_window) {
    glfwSetWindowSize(m_window, m_size.x, m_size.y);
  }
}

Vec2i Window::getSize() {
  if(m_window)
    glfwGetWindowSize(m_window, &m_size.x, &m_size.y);
  return m_size;
}

void Window::update() {
  pollEvents();

  static bool firstCall = true;
  if(m_window && glfwWindowShouldClose(m_window)) {
    if(firstCall) {
      firstCall = false;
    }
    else {
      logWarning("[Window] You should stop your application when "
                 "Window::isValid() returns false! Now closing window...");
      close();
    }
  }
}

void Window::pollEvents() {
  // let glfw poll all events for all windows
  // the callback function will be called and will fill the event queue
  glfwPollEvents();

  // work off queue
  for(auto& e : m_eventQueue) {
    for(auto& callback : m_eventCallbacks) {
      if(callback) {
        callback(e);
      }
    }
  }

  m_eventQueue.clear();

  // window events
  for(auto& e : m_windowEventQueue) {
    for(auto& callback : m_windowCallbacks) {
      if(callback) {
        callback(e);
      }
    }
  }
  
  m_windowEventQueue.clear();
}

bool Window::isValid() {
  return (m_window && !glfwWindowShouldClose(m_window));
}

void Window::postEvent(InputEvent e) {
  m_eventQueue.push_back(e);
}

void Window::postWindowEvent(WindowEvent e) {
  m_windowEventQueue.push_back(e);
}


void Window::resizeCallback(GLFWwindow* win, int width, int height) {
  if(s_eventReceiver.count(win) != 0) {
    // TODO: handle resize (#38)
  }
  else {
    slogAndThrow<WinEx>("A resize event was received on a window, which "
                        "has no managing Window");
  }
}

void Window::keyCallback(GLFWwindow* win, int key, int scancode,
                         int action, int mods) {
  // transcode input into lumina format
  InputEvent e;
  e.type = InputType::Key;
  e.keyInput.key = translateGLFWKey(key);
  switch(action) {
    case GLFW_PRESS:
      e.keyInput.type = KeyInputType::Pressed;
      break;
    case GLFW_RELEASE:
      e.keyInput.type = KeyInputType::Released;
      break;
    case GLFW_REPEAT:
      e.keyInput.type = KeyInputType::Hold;
      break;
  }

  // find the corresponding window and post event
  if(s_eventReceiver.count(win) != 0) {
    s_eventReceiver[win]->postEvent(e);
  }
  else {
    slogAndThrow<WinEx>("A key input was received on a window, which "
                        "has no managing Window");
  }
}


void Window::charCallback(GLFWwindow* win, unsigned int key) {
  // transcode input into lumina format
  InputEvent e;
  e.type = InputType::Key;
  e.keyInput.c = static_cast<char>(key);
  e.keyInput.type = KeyInputType::Char;

  // find the corresponding window and post event
  if(s_eventReceiver.count(win) != 0) {
    s_eventReceiver[win]->postEvent(e);
  }
  else {
    slogAndThrow<WinEx>("A char input was received on a window, which "
                        "has no managing Window");
  }
}

void Window::mouseButtonCallback(GLFWwindow* win, int button, int action,
                                      int mods) {
  // transcode input into lumina format
  InputEvent e;
  e.type = InputType::Mouse;
  switch(button) {
    case GLFW_MOUSE_BUTTON_LEFT:
      e.mouseInput.type = (action == GLFW_PRESS)
                              ? MouseInputType::LButtonPressed
                              : MouseInputType::LButtonReleased;
      break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
      e.mouseInput.type = (action == GLFW_PRESS)
                              ? MouseInputType::MButtonPressed
                              : MouseInputType::MButtonReleased;
      break;

    case GLFW_MOUSE_BUTTON_RIGHT:
      e.mouseInput.type = (action == GLFW_PRESS)
                              ? MouseInputType::RButtonPressed
                              : MouseInputType::RButtonReleased;
      break;
  }

  // find the corresponding window and post event
  if(s_eventReceiver.count(win) != 0) {
    s_eventReceiver[win]->postEvent(e);
  }
  else {
    slogAndThrow<WinEx>("A mouse button input was received on a window, which "
                        "has no managing Window");
  }
}

void Window::mousePosCallback(GLFWwindow* w, double xpos, double ypos) {
  // find the corresponding window and post event
  if(s_eventReceiver.count(w) == 0) {
    slogAndThrow<WinEx>("A mouse pos input was received on a window, which "
                        "has no managing Window");
  }

  // get corresponding window
  auto* win = s_eventReceiver[w];

  // prepare input struct
  InputEvent e;
  e.type = InputType::Mouse;

  if(win->m_cursorMode == CursorMode::Free) {
    if(win->m_resetLastPos) {
      win->m_lastMouseX = static_cast<float>(xpos);
      win->m_lastMouseY = static_cast<float>(ypos);
      e.mouseInput.x = 0.f;
      e.mouseInput.y = 0.f;
      win->m_resetLastPos = false;
    }
    else {
      e.mouseInput.x = static_cast<float>(xpos) - win->m_lastMouseX;
      e.mouseInput.y = static_cast<float>(ypos) - win->m_lastMouseY;
      win->m_lastMouseX = static_cast<float>(xpos);
      win->m_lastMouseY = static_cast<float>(ypos);
    }
    e.mouseInput.type = MouseInputType::MoveDirection;
  }
  else {
    e.mouseInput.x = static_cast<float>(xpos);
    e.mouseInput.y = static_cast<float>(ypos);
    e.mouseInput.type = MouseInputType::MovePosition;
  }

  win->postEvent(e);
}

void Window::mouseScrollCallback(GLFWwindow* w, double x, double y) {
  // find the corresponding window and post event
  if(s_eventReceiver.count(w) == 0) {
    slogAndThrow<WinEx>("A mouse scroll input was received on a window, which "
                        "has no managing Window");
  }

  // get corresponding window
  auto* win = s_eventReceiver[w];

  // prepare input struct
  InputEvent e;
  e.type = InputType::Mouse;
  e.mouseInput.type = MouseInputType::Scroll;
  e.mouseInput.scrollX = static_cast<float>(x);
  e.mouseInput.scrollY = static_cast<float>(y);

  win->postEvent(e);
}

void Window::windowCloseCallback(GLFWwindow* w) {
  if(s_eventReceiver.count(w) == 0) {
    slogAndThrow<WinEx>("A close event was received on a window, which "
                        "has no managing Window");
  }

  WindowEvent e;
  e.type = WindowEventType::Close;

  s_eventReceiver[w]->postWindowEvent(e);
}


}