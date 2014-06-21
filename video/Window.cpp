#include "GLFWTools.hpp"
#include "Window.hpp"

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

RenderContext* Window::getRenderContext() {
  m_renderContext.reset(new RenderContext(m_window));
  return m_renderContext.get();
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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_version.first);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_version.second);
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

  log("[Window] Opened new GLFW window: Success! (Handle: ", m_window, ")");
}

void Window::setVSync(bool enable) {
  glfwSwapInterval(enable ? 1 : 0);
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
  if(m_window && glfwWindowShouldClose(m_window)) {
    close();
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
}

bool Window::isValid() {
  return (m_window && !glfwWindowShouldClose(m_window));
}

void Window::postEvent(LInputEvent e) {
  m_eventQueue.push_back(e);
}

void Window::resizeCallback(GLFWwindow* win, int width, int height) {
  if(s_eventReceiver.count(win) != 0) {
    // something
  }
  else {
    throw runtime_error("A resize event was received on a window, which has no "
      "managing Window");
  }
}

void Window::keyCallback(GLFWwindow* win, int key, int scancode,
                              int action, int mods) {
  // transcode input into lumina format
  LInputEvent e;
  e.type = LInputType::KeyInput;
  e.keyInput.key = translateGLFWKey(key);
  switch(action) {
    case GLFW_PRESS:
      e.keyInput.type = LKeyEventType::KeyPressed;
      break;
    case GLFW_RELEASE:
      e.keyInput.type = LKeyEventType::KeyReleased;
      break;
    case GLFW_REPEAT:
      e.keyInput.type = LKeyEventType::KeyHold;
      break;
  }

  // find the corresponding window and post event
  if(s_eventReceiver.count(win) != 0) {
    s_eventReceiver[win]->postEvent(e);
  }
  else {
    throw runtime_error("A key input was received on a window, which has no "
      "managing Window");
  }
}


void Window::charCallback(GLFWwindow* win, unsigned int key) {
  // transcode input into lumina format
  LInputEvent e;
  e.type = LInputType::KeyInput;
  e.keyInput.c = static_cast<char>(key);
  e.keyInput.type = LKeyEventType::Character;

  // find the corresponding window and post event
  if(s_eventReceiver.count(win) != 0) {
    s_eventReceiver[win]->postEvent(e);
  }
  else {
    throw runtime_error("A char input was received on a window, which has no "
      "managing Window");
  }
}

void Window::mouseButtonCallback(GLFWwindow* win, int button, int action,
                                      int mods) {
  // transcode input into lumina format
  LInputEvent e;
  e.type = LInputType::MouseInput;
  switch(button) {
    case GLFW_MOUSE_BUTTON_LEFT:
      e.mouseInput.type = (action == GLFW_PRESS)
                              ? LMouseEventType::LButtonPressed
                              : LMouseEventType::LButtonReleased;
      break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
      e.mouseInput.type = (action == GLFW_PRESS)
                              ? LMouseEventType::MButtonPressed
                              : LMouseEventType::MButtonReleased;
      break;

    case GLFW_MOUSE_BUTTON_RIGHT:
      e.mouseInput.type = (action == GLFW_PRESS)
                              ? LMouseEventType::RButtonPressed
                              : LMouseEventType::RButtonReleased;
      break;
  }

  // find the corresponding window and post event
  if(s_eventReceiver.count(win) != 0) {
    s_eventReceiver[win]->postEvent(e);
  }
  else {
    throw runtime_error("A char input was received on a window, which has no "
      "managing Window");
  }
}

}