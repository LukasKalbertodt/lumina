namespace lumina {


RenderBuffer::RenderBuffer() : m_handle(0) {}

RenderBufferType RenderBuffer::getType() const {
  return m_type;
}

GLuint RenderBuffer::nativeHandle() const {
  return m_handle;
}


}