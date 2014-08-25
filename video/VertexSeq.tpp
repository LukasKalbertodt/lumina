namespace lumina {

// =============================================================================
// VertexSeqBase
// =============================================================================
namespace internal {

inline VertexSeqBase::VertexSeqBase() 
  : m_vertexHandle(0),
    m_indexHandle(0),
    m_vertexArrayObject(0),
    m_vertexCount(0),
    m_indexCount(0),
    m_layoutActive(false) {}

inline VertexSeqBase::VertexSeqBase(VertexSeqBase&& m) noexcept
  : m_vertexHandle(m.m_vertexHandle),
    m_indexHandle(m.m_indexHandle),
    m_vertexArrayObject(m.m_vertexArrayObject),
    m_vertexCount(m.m_vertexCount),
    m_indexCount(m.m_indexCount),
    m_layoutActive(m.m_layoutActive) {
  // reset values of m
  m.m_vertexHandle = 0;
  m.m_indexHandle = 0;
  m.m_vertexArrayObject = 0;
  m.m_vertexCount = 0;
  m.m_indexCount = 0;
  m.m_layoutActive = false;
}

inline VertexSeqBase::~VertexSeqBase() {
  // glDelete* does nothing if second argument is 0
  glDeleteBuffers(1, &m_vertexHandle);
  glDeleteBuffers(1, &m_indexHandle);
  glDeleteVertexArrays(1, &m_vertexArrayObject);
}

inline VertexSeqBase& VertexSeqBase::operator=(VertexSeqBase m) {
  // swap all members
  std::swap(m_vertexHandle, m.m_vertexHandle);
  std::swap(m_indexHandle, m.m_indexHandle);
  std::swap(m_vertexArrayObject, m.m_vertexArrayObject);
  std::swap(m_vertexCount, m.m_vertexCount);
  std::swap(m_indexCount, m.m_indexCount);
  std::swap(m_layoutActive, m.m_layoutActive);

  // dtor of m will cleanup the rest
  return *this;
}

inline GLuint VertexSeqBase::nativeVertexHandle() const {
  return m_vertexHandle;
}

inline GLuint VertexSeqBase::nativeIndexHandle() const {
  return m_indexHandle;
}

inline GLuint VertexSeqBase::nativeVAOHandle() const {
  return m_vertexArrayObject;
}

inline uint32_t VertexSeqBase::vertexCount() const {
  return m_vertexCount;  
}

inline uint32_t VertexSeqBase::indexCount() const {
  return m_indexCount;
}

inline int VertexSeqBase::size() const {
  return (m_indexHandle == 0) ? m_vertexCount : m_indexCount;
}

inline bool VertexSeqBase::isLayoutActive() const {
  return m_layoutActive;
}

inline VertexSeqBase::operator bool() const {
   return (m_vertexHandle != 0);
}

inline void VertexSeqBase::bindAll() {
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
  glBindVertexArray(m_vertexArrayObject);
}

inline void VertexSeqBase::unbindAll() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

inline void VertexSeqBase::bindVAO() const {
  glBindVertexArray(m_vertexArrayObject);
}

inline void VertexSeqBase::unbindVAO() const {
  glBindVertexArray(m_vertexArrayObject);
}

inline void VertexSeqBase::setupOpenGL() {
  // configure primitive restart
  glPrimitiveRestartIndex(std::numeric_limits<unsigned int>::max());
  glEnable(GL_PRIMITIVE_RESTART);
}

} // namespace internal



// =============================================================================
// VertexSeq
// =============================================================================
template <typename... Ts>
void VertexSeq<Ts...>::create(uint32_t vertexCount, uint32_t indexCount) {
  internal::VertexSeqBase::create(internal::VertexLayout<Ts...>::size,
                                  vertexCount, indexCount);
}

template <typename... Ts>
void VertexSeq<Ts...>::prime(std::function<void(HotVertexSeq<Ts...>&)> func) {
  // ===== pre-prime =====
  // check if any VertexSeq is already primed
  if(VertexSeq::s_isPrimed) {
    logThrowGL("[HotVertexSeq] Attempt to prime a VertexSeq while another is "
               "already primed!");
  }

  // set prime marker
  VertexSeqBase::s_isPrimed = true;

  // bind VAO and VBO (for mapping)
  bindAll();

  // map vertex buffer
  void* mappedVBuf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

  // map index buffer, if it exists
  void* mappedIBuf = nullptr;
  if(m_indexHandle != 0) {
    mappedIBuf = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    if(!mappedIBuf) {
      logThrowGL("[HotVertexSeq] Error while mapping index buffer!");
    }
  }

  checkGLError("[VertexSeq] OpenGL error<", GLERR, "> while pre-prime!");


  // ===== call given functor =====
  HotVertexSeq<Ts...> hot(*this, mappedVBuf, mappedIBuf);
  func(hot);

  checkGLError("[VertexSeq] OpenGL error<", GLERR, "> after prime!");


  // ===== post-prime =====
  // apply vertex layout
  if(!m_layoutActive) {
    internal::
      applyVertexLayout<0, internal::VertexLayout<Ts...>::size, 0, Ts...>();

    checkGLError("[HotVertexSeq] Error<", GLERR, 
                 "> while applying vertex layout!");
    m_layoutActive = true;
  }

  // unmap buffers
  glUnmapBuffer(GL_ARRAY_BUFFER);
  if(mappedIBuf) {
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
  }

  // unbind buffers and VAO
  unbindAll();

  // check for GL error 
  checkGLError("[VertexSeq] OpenGL error<", GLERR, "> while post-prime!");

  // remove prime marker
  VertexSeq::s_isPrimed = false;
}

} // namespace lumina