namespace lumina {

inline RenderContext::RenderContext(GLFWwindow* window)
  : m_windowHandle(window),
    m_defaultFB(std::make_shared<internal::DefaultFrameBuffer>()) {}

inline FrameBuffer& RenderContext::getDefaultFrameBuffer() {
  return m_defaultFB;
}

}