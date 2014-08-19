namespace lumina {


inline RenderBuffer::RenderBuffer() : m_handle(0) {}

inline RenderBufferType RenderBuffer::getType() const {
  return m_type;
}

inline GLuint RenderBuffer::nativeHandle() const {
  return m_handle;
}


}