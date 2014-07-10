namespace lumina {

template <typename... Cs>
HotVertexSeq<Cs...>::HotVertexSeq(VertexSeq& ref)
  : m_cold(ref), vertex(ref.m_vertexCount), index(ref.m_indexCount) {
  // check if a vertex seq is already primed... if not, set primed marker
  if(VertexSeq::s_isPrimed) {
    logError(
      "[HotVertexSeq] Attempt to prime a VertexSeq while another is already "
      "primed!");
    throw GLException(
      "[HotVertexSeq] Attempt to prime a VertexSeq while another is "
      "already primed!");
  }
  VertexSeq::s_isPrimed = true;

  // bind all objects
  m_cold.bindAll();

  // map vertex buffer
  vertex.m_buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

  // map index buffer, if it exists
  if(m_cold.m_indexHandle != 0) {
    index.m_buffer = static_cast<unsigned int*>(
      glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE));
  }

  // check for error
  checkGLError("[HotVertexSeq] Error <", GLERR, "> while creating HotVertexSeq!");
}

// unmap and unbind all buffers
template <typename... Cs>
HotVertexSeq<Cs...>::~HotVertexSeq() {
  glUnmapBuffer(GL_ARRAY_BUFFER);
  if(index.m_buffer) {
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
  }

  // unmap buffers and VAO
  m_cold.unbindAll();

  // check for error (remember: never evaar throw in dtor!)
  checkGLWarning("[HotVertexSeq] OpenGL error<", GLERR, "> in HotVertexSeq destructor!");

  // remove primed marker
  VertexSeq::s_isPrimed = false;
}

template <typename... Cs>
void HotVertexSeq<Cs...>::applyVertexLayout() {
  internal::applyLayoutImpl<0, internal::LayoutTypes<Cs...>::stride,
                            0, sizeof(Cs)...>();

  checkGLError("[HotVertexSeq] Error<", GLERR, "> while applying vertex layout!");
}

}  // namespace lumina