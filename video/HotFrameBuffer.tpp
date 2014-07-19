namespace lumina {

HotFrameBuffer::HotFrameBuffer(FrameBuffer& cold) : m_cold(cold) {
  // FrameBuffer::prime checked if another FrameBuffer is primed...
  cold.bind();
  cold.updateState();

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    logThrowGL(
      "[FrameBuffer] Framebuffer status is not complete after priming!");
  }
}

HotFrameBuffer::~HotFrameBuffer() {
  m_cold.unbind();
}


}