namespace lumina {

/* Mesh constructors **********************************************************/
inline VertexSeq::VertexSeq()
  : m_vertexHandle(0),
    m_indexHandle(0),
    m_vertexArrayObject(0),
    m_vertexCount(0),
    m_indexCount(0),
    m_vertexSize(0),
    m_layoutActive(false) {
  setupOpenGL();
}

// copy constructor and copy assignment operator
// inline VertexSeq::VertexSeq(const VertexSeq& copy);
// inline VertexSeq& operator=(const VertexSeq& copy);

// move constructor and move assignment operator
inline VertexSeq::VertexSeq(VertexSeq&& m)
  : m_vertexHandle(m.m_vertexHandle),
    m_indexHandle(m.m_indexHandle),
    m_vertexArrayObject(m.m_vertexArrayObject),
    m_vertexCount(m.m_vertexCount),
    m_indexCount(m.m_indexCount),
    m_vertexSize(m.m_vertexSize),
    m_layoutActive(m.m_layoutActive) {
  // reset values of m
  m.m_vertexHandle = 0;
  m.m_indexHandle = 0;
  m.m_vertexArrayObject = 0;
  m.m_vertexCount = 0;
  m.m_indexCount = 0;

  // don't need to call setupOpenGL(), because it already was by m
}
// inline VertexSeq& operator=(VertexSeq&& m);


/* VertexSeq methods ***************************************************************/
// inline std::size_t VertexSeq::vertexCount() const { return m_vertexCount; }
// inline std::size_t VertexSeq::indexCount() const { return m_indexCount; }
// inline std::size_t VertexSeq::vertexSize() const { return m_vertexCount * 4; }
// inline std::size_t VertexSeq::indexSize() const { return m_indexCount * 4; }

template <typename... Cs, typename L>
void VertexSeq::prime(L lambda) {
  HotVertexSeq<Cs...> hot(*this);
  lambda(hot);
}

inline void VertexSeq::bindAll() {
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
  glBindVertexArray(m_vertexArrayObject);
}

inline void VertexSeq::bindVAO() const {
  glBindVertexArray(m_vertexArrayObject);
}

inline void VertexSeq::unbindVAO() const {
  glBindVertexArray(m_vertexArrayObject);
}


inline void VertexSeq::unbindAll() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

inline GLuint VertexSeq::nativeVertexHandle() const {
  return m_vertexHandle;
}

inline GLuint VertexSeq::nativeIndexHandle() const {
  return m_indexHandle;
}

inline GLuint VertexSeq::nativeVAOHandle() const {
  return m_vertexArrayObject;
}

inline int VertexSeq::size() const {
  return (m_indexHandle == 0) ? m_vertexCount : m_indexCount;
}

inline bool VertexSeq::isVertexLayoutActive() const {
  return m_layoutActive;
}

} // namespace lumina