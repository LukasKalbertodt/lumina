#include "LWindow.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

namespace lumina {

// static member: map GLFWwindow to instances of LWindow for event dispatch
std::map<GLFWwindow*, LWindow*> LWindow::s_eventReceiver;


LWindow::~LWindow() {
  if(m_window) {
    close();
  }
}

LRenderContext* LWindow::getRenderContext() {
  m_renderContext.reset(new LRenderContext(m_window));
  return m_renderContext.get();
}

void LWindow::open() {
   // Init GLFW (TODO: do this just once)
  if(!glfwInit()) {
    logError("[LWindow] GLFW initialization failed!");
    throw runtime_error("GLFW initialization failed");
  }

  // set window hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_version.first);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_version.second);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // Create window
  m_window
      = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), nullptr, nullptr);
  if(!m_window) {
    // glfwTerminate();  // TODO: cleanup neccessary?
    logError("[LWindow] GLFW window creation failed");
    throw runtime_error("GLFW window creation failed");
  }

  // check attributes
  int major = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MAJOR);
  int minor = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MINOR);
  if(major != m_version.first || minor != m_version.second) {
    logWarning("[LWindow] Actual version <",
               major, ".", minor,
               "> differs from version hint <",
               m_version.first, ".", m_version.second,
               ">!");
  }

  // add to list of event receiving windows
  s_eventReceiver[m_window] = this;

  // prepare event callbacks
  glfwSetWindowSizeCallback(m_window, LWindow::resizeCallback);
  glfwSetKeyCallback(m_window, LWindow::keyCallback);
  glfwSetCharCallback(m_window, LWindow::charCallback);
  glfwSetMouseButtonCallback(m_window, LWindow::mouseButtonCallback);

  glfwMakeContextCurrent(m_window);

  log("[LWindow] Opened new GLFW window: Success! (Handle: ", m_window, ")");
}

void LWindow::setVSync(bool enable) {
  glfwSwapInterval(enable ? 1 : 0);
}


void LWindow::close() {
  if(m_window) {
    glfwDestroyWindow(m_window);
    s_eventReceiver.erase(m_window);
    log("[LWindow] Destroyed GLFW window. (Handle: ", m_window, ")");
    m_window = nullptr;

    if(s_eventReceiver.empty()) {
      glfwTerminate();
      log("[LWindow] Last window was destroyed, called glfwTerminate: Success!");
    }
  }
  else {
    logWarning("[LWindow] Attempting to close a GLFW window, "
      "which is not open!");
  }
}

void LWindow::setTitle(std::string title) {
  m_title = title;
  if(m_window) {
    glfwSetWindowTitle(m_window, title.c_str());
  }
}

void LWindow::resize(Vec2i size) {
  m_size = size;
  if(m_window) {
    glfwSetWindowSize(m_window, m_size.x, m_size.y);
  }
}

Vec2i LWindow::getSize() {
  if(m_window)
    glfwGetWindowSize(m_window, &m_size.x, &m_size.y);
  return m_size;
}

void LWindow::update() {
  pollEvents();
  if(m_window && glfwWindowShouldClose(m_window)) {
    close();
  }
}

void LWindow::pollEvents() {
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

bool LWindow::isValid() {
  return (m_window && !glfwWindowShouldClose(m_window));
}

void LWindow::postEvent(LInputEvent e) {
  m_eventQueue.push_back(e);
}

void LWindow::resizeCallback(GLFWwindow* win, int width, int height) {
  if(s_eventReceiver.count(win) != 0) {
    // something
  }
  else {
    throw runtime_error("A resize event was received on a window, which has no "
      "managing LWindow");
  }
}

void LWindow::keyCallback(GLFWwindow* win, int key, int scancode,
                              int action, int mods) {
  // transcode input into lumina format
  LInputEvent e;
  e.type = LInputType::KeyInput;
  e.keyInput.key = translateKey(key);
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
      "managing LWindow");
  }
}


void LWindow::charCallback(GLFWwindow* win, unsigned int key) {
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
      "managing LWindow");
  }
}

void LWindow::mouseButtonCallback(GLFWwindow* win, int button, int action,
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
      "managing LWindow");
  }
}

LKeyCode LWindow::translateKey(int key)
{
  switch(key)
  {
    case GLFW_KEY_BACKSPACE:     return LKeyCode::Backspace;
    case GLFW_KEY_TAB:           return LKeyCode::Tab;
    case GLFW_KEY_KP_ENTER:
    case GLFW_KEY_ENTER:         return LKeyCode::Return;
    case GLFW_KEY_LEFT_SHIFT:
    case GLFW_KEY_RIGHT_SHIFT:   return LKeyCode::Shift;
    case GLFW_KEY_LEFT_CONTROL:
    case GLFW_KEY_RIGHT_CONTROL: return LKeyCode::Control;
    case GLFW_KEY_LEFT_ALT:
    case GLFW_KEY_RIGHT_ALT:     return LKeyCode::Alt;
    case GLFW_KEY_PAUSE:         return LKeyCode::Pause;
    case GLFW_KEY_CAPS_LOCK:     return LKeyCode::Capital;
    case GLFW_KEY_ESCAPE:        return LKeyCode::Escape;
    case GLFW_KEY_SPACE:         return LKeyCode::Space;
    case GLFW_KEY_PAGE_UP:       return LKeyCode::Pageup;
    case GLFW_KEY_PAGE_DOWN:     return LKeyCode::Pagedown;
    case GLFW_KEY_END:           return LKeyCode::End;
    case GLFW_KEY_HOME:          return LKeyCode::Home;
    case GLFW_KEY_LEFT:          return LKeyCode::Left;
    case GLFW_KEY_UP:            return LKeyCode::Up;
    case GLFW_KEY_RIGHT:         return LKeyCode::Right;
    case GLFW_KEY_DOWN:          return LKeyCode::Down;
    case GLFW_KEY_PRINT_SCREEN:  return LKeyCode::Snapshot;
    case GLFW_KEY_INSERT:        return LKeyCode::Insert;
    case GLFW_KEY_DELETE:        return LKeyCode::Delete;
    case GLFW_KEY_0:             return LKeyCode::K0;
    case GLFW_KEY_1:             return LKeyCode::K1;
    case GLFW_KEY_2:             return LKeyCode::K2;
    case GLFW_KEY_3:             return LKeyCode::K3;
    case GLFW_KEY_4:             return LKeyCode::K4;
    case GLFW_KEY_5:             return LKeyCode::K5;
    case GLFW_KEY_6:             return LKeyCode::K6;
    case GLFW_KEY_7:             return LKeyCode::K7;
    case GLFW_KEY_8:             return LKeyCode::K8;
    case GLFW_KEY_9:             return LKeyCode::K9;
    case GLFW_KEY_A:             return LKeyCode::A;
    case GLFW_KEY_B:             return LKeyCode::B;
    case GLFW_KEY_C:             return LKeyCode::C;
    case GLFW_KEY_D:             return LKeyCode::D;
    case GLFW_KEY_E:             return LKeyCode::E;
    case GLFW_KEY_F:             return LKeyCode::F;
    case GLFW_KEY_G:             return LKeyCode::G;
    case GLFW_KEY_H:             return LKeyCode::H;
    case GLFW_KEY_I:             return LKeyCode::I;
    case GLFW_KEY_J:             return LKeyCode::J;
    case GLFW_KEY_K:             return LKeyCode::K;
    case GLFW_KEY_L:             return LKeyCode::L;
    case GLFW_KEY_M:             return LKeyCode::M;
    case GLFW_KEY_N:             return LKeyCode::N;
    case GLFW_KEY_O:             return LKeyCode::O;
    case GLFW_KEY_P:             return LKeyCode::P;
    case GLFW_KEY_Q:             return LKeyCode::Q;
    case GLFW_KEY_R:             return LKeyCode::R;
    case GLFW_KEY_S:             return LKeyCode::S;
    case GLFW_KEY_T:             return LKeyCode::T;
    case GLFW_KEY_U:             return LKeyCode::U;
    case GLFW_KEY_V:             return LKeyCode::V;
    case GLFW_KEY_W:             return LKeyCode::W;
    case GLFW_KEY_X:             return LKeyCode::X;
    case GLFW_KEY_Y:             return LKeyCode::Y;
    case GLFW_KEY_Z:             return LKeyCode::Z;
    case GLFW_KEY_LEFT_SUPER:    return LKeyCode::LWin;
    case GLFW_KEY_RIGHT_SUPER:   return LKeyCode::RWin;
    case GLFW_KEY_MENU:          return LKeyCode::Apps;
    case GLFW_KEY_KP_0:          return LKeyCode::Numpad0;
    case GLFW_KEY_KP_1:          return LKeyCode::Numpad1;
    case GLFW_KEY_KP_2:          return LKeyCode::Numpad2;
    case GLFW_KEY_KP_3:          return LKeyCode::Numpad3;
    case GLFW_KEY_KP_4:          return LKeyCode::Numpad4;
    case GLFW_KEY_KP_5:          return LKeyCode::Numpad5;
    case GLFW_KEY_KP_6:          return LKeyCode::Numpad6;
    case GLFW_KEY_KP_7:          return LKeyCode::Numpad7;
    case GLFW_KEY_KP_8:          return LKeyCode::Numpad8;
    case GLFW_KEY_KP_9:          return LKeyCode::Numpad9;
    case GLFW_KEY_KP_MULTIPLY:   return LKeyCode::Multiply;
    case GLFW_KEY_KP_ADD:        return LKeyCode::Add;
    case GLFW_KEY_KP_SUBTRACT:   return LKeyCode::Subtract;
    case GLFW_KEY_KP_DECIMAL:    return LKeyCode::Decimal;
    case GLFW_KEY_KP_DIVIDE:     return LKeyCode::Divide;
    case GLFW_KEY_F1:            return LKeyCode::F1;
    case GLFW_KEY_F2:            return LKeyCode::F2;
    case GLFW_KEY_F3:            return LKeyCode::F3;
    case GLFW_KEY_F4:            return LKeyCode::F4;
    case GLFW_KEY_F5:            return LKeyCode::F5;
    case GLFW_KEY_F6:            return LKeyCode::F6;
    case GLFW_KEY_F7:            return LKeyCode::F7;
    case GLFW_KEY_F8:            return LKeyCode::F8;
    case GLFW_KEY_F9:            return LKeyCode::F9;
    case GLFW_KEY_F10:           return LKeyCode::F10;
    case GLFW_KEY_F11:           return LKeyCode::F11;
    case GLFW_KEY_F12:           return LKeyCode::F12;
    case GLFW_KEY_F13:           return LKeyCode::F13;
    case GLFW_KEY_F14:           return LKeyCode::F14;
    case GLFW_KEY_F15:           return LKeyCode::F15;
    case GLFW_KEY_F16:           return LKeyCode::F16;
    case GLFW_KEY_F17:           return LKeyCode::F17;
    case GLFW_KEY_F18:           return LKeyCode::F18;
    case GLFW_KEY_F19:           return LKeyCode::F19;
    case GLFW_KEY_F20:           return LKeyCode::F20;
    case GLFW_KEY_F21:           return LKeyCode::F21;
    case GLFW_KEY_F22:           return LKeyCode::F22;
    case GLFW_KEY_F23:           return LKeyCode::F23;
    case GLFW_KEY_F24:           return LKeyCode::F24;
    case GLFW_KEY_NUM_LOCK:      return LKeyCode::Numlock;
    case GLFW_KEY_SCROLL_LOCK:   return LKeyCode::Scroll;
    case GLFW_KEY_SEMICOLON:     return LKeyCode::OEM_1;
    case GLFW_KEY_SLASH:         return LKeyCode::OEM_2;
    case GLFW_KEY_GRAVE_ACCENT:  return LKeyCode::OEM_3;
    case GLFW_KEY_LEFT_BRACKET:  return LKeyCode::OEM_4;
    case GLFW_KEY_BACKSLASH:     return LKeyCode::OEM_5;
    case GLFW_KEY_RIGHT_BRACKET: return LKeyCode::OEM_6;
    case GLFW_KEY_APOSTROPHE:    return LKeyCode::OEM_7;
    case GLFW_KEY_WORLD_1:       return LKeyCode::OEM_8;
    case GLFW_KEY_WORLD_2:       return LKeyCode::OEM_102;
    case GLFW_KEY_EQUAL:         return LKeyCode::OEM_Plus;
    case GLFW_KEY_COMMA:         return LKeyCode::OEM_Comma;
    case GLFW_KEY_MINUS:         return LKeyCode::OEM_Minus;
    case GLFW_KEY_PERIOD:        return LKeyCode::OEM_Period;
    default: return LKeyCode::None;
  }
}

}