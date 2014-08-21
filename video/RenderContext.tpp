namespace lumina {

inline RenderContext::RenderContext(GLFWwindow* window, Vec2i size)
  : m_windowHandle(window),
    m_defaultFB(std::make_shared<internal::DefaultFrameBuffer>()),
    m_wasCreated(false) {
  m_defaultFB.create(size);
}

inline HotRenderContext& RenderContext::getCurrentContext() {
  if(!s_primedContext) {
    slogAndThrow<GLException>("[RenderContext] Current context requested but "
                              " no context is current!");
  }
  return *s_primedContext;
}

inline bool RenderContext::isContextCurrent() {
  return (s_primedContext != nullptr);
}

}