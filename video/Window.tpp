namespace lumina {

inline Window::Window(std::string title, Vec2i size)
  : m_window(nullptr),
    m_size(size),
    m_version(1, 1),
    m_title(title),
    m_lastMouseX(0.f),
    m_lastMouseY(0.f),
    m_resetLastPos(true) {}


inline void Window::setVersionHint(int major, int minor) {
  m_version = std::pair<std::int16_t, std::int16_t>(major, minor);
}

inline Window::CallbackAccessor Window::addEventCallback(
  EventCallback&& callback) {
  m_eventCallbacks.push_back(std::forward<EventCallback>(callback));
  return m_eventCallbacks.size() - 1;
}

inline void Window::removeEventCallback(Window::CallbackAccessor accessor) {
  m_eventCallbacks[accessor] = EventCallback();
}


} // namespace lumina