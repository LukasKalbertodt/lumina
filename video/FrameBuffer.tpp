namespace lumina {

inline FrameBuffer::FrameBuffer() : m_handle(0), m_needsUpdate(true) {}
inline FrameBuffer::FrameBuffer(FrameBuffer&& o)
  : m_handle(o.m_handle), m_needsUpdate(o.m_needsUpdate) {
  // reset handle of moved object
  o.m_handle = 0;
  o.m_needsUpdate = true;
}

inline FrameBuffer::~FrameBuffer() {
  // opengl will ignore a 0-handle
  glDeleteFramebuffers(1, &m_handle);
}

inline void FrameBuffer::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
  s_isPrimed = true;
}

inline void FrameBuffer::unbind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  s_isPrimed = false;
}

inline internal::FBAttachmentPoint FrameBuffer::operator[](int index) {
  if(index >= m_attachments.size()) {
    logAndThrow<OutOfRangeEx>("[FrameBuffer] Index<", index, 
                              "> out of bounds<", m_attachments.size(), ">!");
  }
  return internal::FBAttachmentPoint(m_attachments[index], m_needsUpdate);
}


}