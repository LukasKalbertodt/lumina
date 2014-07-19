namespace lumina {

namespace internal {

HotVertexSeqBase::HotVertexSeqBase(VertexSeq& ref)
  : cold(ref), index(ref.m_indexCount) {
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
  cold.bindAll();
  // cold.bindVAO();

  // map index buffer, if it exists
  if(cold.nativeIndexHandle() != 0) {
    index.m_buffer = static_cast<unsigned int*>(
      glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE));
    if(index.m_buffer == nullptr) {
      logError("[HotVertexSeq] Error while mapping index buffer!");
      throw GLException("[HotVertexSeq] Error while mapping index buffer!");
    }
  }

  // error check in derived classes
}

// unmap and unbind all buffers
HotVertexSeqBase::~HotVertexSeqBase() {
  glUnmapBuffer(GL_ARRAY_BUFFER);
  if(index.m_buffer) {
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
  }

  // unmap buffers and VAO
  cold.unbindAll();

  // check for error (remember: never evaar throw in dtor!)
  checkGLWarning("[HotVertexSeq] OpenGL error<", GLERR, 
                 "> in HotVertexSeq destructor!");

  // remove primed marker
  VertexSeq::s_isPrimed = false;
}

} // namespace internal


template <typename... Cs>
HotVertexSeq<Cs...>::HotVertexSeq(VertexSeq& ref) 
  : internal::HotVertexSeqBase(ref), vertex(ref.m_vertexCount) {
  // map vertex buffer
  vertex.m_buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

  // check for error
  checkGLError("[HotVertexSeq] Error <", GLERR, 
               "> while creating HotVertexSeq!");
}


HotVertexSeq<>::HotVertexSeq(VertexSeq& ref)
  : internal::HotVertexSeqBase(ref),
    vertex(ref.m_vertexCount, ref.m_vertexSize) {
  // map vertex buffer
  vertex.m_buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

  // check for error
  checkGLError("[HotVertexSeq] Error <", GLERR, 
               "> while creating HotVertexSeq!");
}


template <typename... Cs>
void HotVertexSeq<Cs...>::applyVertexLayout() {
  internal::applyLayoutImpl<0, internal::LayoutTypes<Cs...>::stride,
                            0, sizeof(Cs)...>();

  checkGLError("[HotVertexSeq] Error<", GLERR, 
               "> while applying vertex layout!");
}

template <typename... Cs>
void HotVertexSeq<>::applyVertexLayout() {
  internal::applyLayoutImpl<0, internal::LayoutTypes<Cs...>::stride,
                            0, sizeof(Cs)...>();

  checkGLError("[HotVertexSeq] Error<", GLERR, 
               "> while applying vertex layout!");
}

}  // namespace lumina