namespace lumina {

inline HotFrameBuffer::HotFrameBuffer(FrameBuffer& cold)
  : colors(cold.m_colorAtts), m_cold(cold) {
  // FrameBuffer::prime checked if another FrameBuffer is primed...
  cold.bind();
  cold.updateState();

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    logThrowGL(
      "[FrameBuffer] Framebuffer status is not complete after priming!");
  }
}

inline HotFrameBuffer::~HotFrameBuffer() {
  m_cold.unbind();
}


}