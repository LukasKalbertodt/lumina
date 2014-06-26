namespace lumina {

FrameBuffer::FrameBuffer() : m_handle(0) {}
FrameBuffer::FrameBuffer(FrameBuffer o) : m_handle(o.m_handle) {
  // reset handle of moved object
  o.m_handle = 0;
}

FrameBuffer::~FrameBuffer() {
  // opengl will ignore a 0-handle
  glDeleteFramebuffers(1, &m_handle);
}

}