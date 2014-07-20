namespace lumina {

inline HotFrameBuffer::HotFrameBuffer(
  std::shared_ptr<internal::FrameBufferInterface> cold)
  : m_cold(cold) {}
}