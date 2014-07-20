namespace lumina {

inline HotFrameBuffer::HotFrameBuffer(
  std::shared_ptr<internal::FrameBufferInterface> cold)
  : m_cold(cold) {}


inline void HotFrameBuffer::clearColor(int index, Color32fA color) {
  m_cold->clearColor(index, color);
}

}
