namespace lumina {

namespace internal {

inline UserFrameBuffer::UserFrameBuffer()
  : m_handle(0),
    m_depthAtt(0),
    m_depthStencilAtt(0),
    m_renderBuffer(0),
    m_needsUpdate(true) {}

inline UserFrameBuffer::UserFrameBuffer(UserFrameBuffer&& o)
  : m_handle(o.m_handle), m_needsUpdate(o.m_needsUpdate) {
  // reset handle of moved object
  o.m_handle = 0;
  o.m_needsUpdate = true;
}

inline UserFrameBuffer::~UserFrameBuffer() {
  // opengl will ignore a 0-handle
  glDeleteFramebuffers(1, &m_handle);
}

inline void UserFrameBuffer::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
  s_isPrimed = true;
}

inline void UserFrameBuffer::unbind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  s_isPrimed = false;
}




inline void DefaultFrameBuffer::create(Vec2i size) {}

} // namespace internal


inline FrameBuffer::FrameBuffer() 
  : m_fb(new internal::UserFrameBuffer()) {}

inline FrameBuffer::FrameBuffer(
  std::shared_ptr<internal::FrameBufferInterface> fb)
  : m_fb(move(fb)) {}


inline void FrameBuffer::create(Vec2i size) {
  m_fb->create(size);
}
inline void FrameBuffer::prime(std::function<void(HotFrameBuffer&)> func) {
  m_fb->prime(m_fb, func);
}

inline void FrameBuffer::attachColor(int index, const Tex2D& tex) {
  m_fb->attachColor(index, tex);
}
inline void FrameBuffer::attachDepth(const Tex2D& tex) {
  m_fb->attachDepth(tex);
}
inline void FrameBuffer::attachDepthStencil(const Tex2D& tex) {
  m_fb->attachDepthStencil(tex);
}

inline bool FrameBuffer::isPrimed() {
  return internal::FrameBufferInterface::s_isPrimed;
}

inline void FrameBuffer::addDefaultBuffer(RenderBufferType type) {
  m_fb->addDefaultBuffer(type);
}

}