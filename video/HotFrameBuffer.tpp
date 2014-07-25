namespace lumina {

inline HotFrameBuffer::HotFrameBuffer(
  std::shared_ptr<internal::FrameBufferInterface> cold)
  : m_cold(cold) {}


inline void HotFrameBuffer::clearColor(int index, Color32fA color) {
  m_cold->clearColor(index, color);
}

inline void HotFrameBuffer::clearDepth(float val) {
  m_cold->clearDepth(val);
}

inline void HotFrameBuffer::clearDepthStencil(float depth, int stencil) {
  m_cold->clearDepthStencil(depth, stencil);
}


}
