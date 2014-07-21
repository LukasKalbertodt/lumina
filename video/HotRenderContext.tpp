namespace lumina {

inline HotRenderContext::HotRenderContext(RenderContext& cold) : m_cold(cold) {}

inline HotRenderContext::~HotRenderContext() {}


inline FrameBuffer& HotRenderContext::getDefaultFrameBuffer() {
  return m_cold.m_defaultFB;
}


}