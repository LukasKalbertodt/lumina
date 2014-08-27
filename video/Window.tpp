namespace lumina {

inline Window::Window(std::string title, Vec2i size)
  : m_window(nullptr),
    m_size(size),
    m_version(0, 0),
    m_title(title),
    m_lastMouseX(0.f),
    m_lastMouseY(0.f),
    m_sizeMultiplier(1.f),
    m_resetLastPos(true),
    m_resizable(false),
    m_fullscreen(false) {}


inline void Window::setVersionHint(int major, int minor) {
  m_version = std::pair<std::int16_t, std::int16_t>(major, minor);
}

inline Window::EventCallbackIndex Window::addEventCallback(
  EventCallback&& callback) {
  m_eventCallbacks.push_back(std::forward<EventCallback>(callback));
  return m_eventCallbacks.size() - 1;
}

inline void Window::removeEventCallback(Window::EventCallbackIndex index) {
  m_eventCallbacks[index] = EventCallback();
}


inline Window::WindowCallbackIndex Window::addWindowCallback(
  WindowCallback&& callback) {
  m_windowCallbacks.push_back(std::forward<WindowCallback>(callback));
  return m_windowCallbacks.size() - 1;
}

inline void Window::removeWindowCallback(WindowCallbackIndex index) {
  m_windowCallbacks[index] = WindowCallback();
}

inline void Window::setFullscreen(bool enable) {
  m_fullscreen = enable;
}


inline void Window::setResizable(bool enable) {
  m_resizable = enable;
}

inline void Window::setSizeMultiplier(float multi) {
  m_sizeMultiplier = multi;
}




} // namespace lumina