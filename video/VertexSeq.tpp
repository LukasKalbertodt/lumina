namespace lumina {

/* Mesh constructors **********************************************************/
template <typename... Ts>
inline VertexSeq<Ts...>::VertexSeq()
  : m_vertexHandle(0),
    m_indexHandle(0),
    m_vertexArrayObject(0),
    m_vertexCount(0),
    m_indexCount(0),
    m_vertexSize(0),
    m_layoutActive(false) {}

// copy constructor and copy assignment operator
// inline VertexSeq::VertexSeq(const VertexSeq& copy);
// inline VertexSeq& operator=(const VertexSeq& copy);

// move constructor and move assignment operator
template <typename... Ts> 
VertexSeq<Ts...>::VertexSeq(VertexSeq&& m)
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
}

template <typename... Ts> 
VertexSeq<Ts...>& VertexSeq<Ts...>::operator=(VertexSeq&& m) {
  // delete OpenGL data
  // glDelete* does nothing if second argument is 0
  glDeleteBuffers(1, &m_vertexHandle);
  glDeleteBuffers(1, &m_indexHandle);
  glDeleteVertexArrays(1, &m_vertexArrayObject);

  // copy data
  m_vertexHandle = m.m_vertexHandle;
  m_indexHandle = m.m_indexHandle;
  m_vertexArrayObject = m.m_vertexArrayObject;
  m_vertexCount = m.m_vertexCount;
  m_indexCount = m.m_indexCount;
  m_vertexSize = m.m_vertexSize;
  m_layoutActive = m.m_layoutActive;

  // reset old values
  m.m_vertexHandle = 0;
  m.m_indexHandle = 0;
  m.m_vertexArrayObject = 0;
  m.m_vertexCount = 0;
  m.m_indexCount = 0;

  return *this;
}


/* VertexSeq methods ***************************************************************/
// inline std::size_t VertexSeq::vertexCount() const { return m_vertexCount; }
// inline std::size_t VertexSeq::indexCount() const { return m_indexCount; }
// inline std::size_t VertexSeq::vertexSize() const { return m_vertexCount * 4; }
// inline std::size_t VertexSeq::indexSize() const { return m_indexCount * 4; }

// template <typename... Ts>
// template <typename L>
// void VertexSeq<Ts...>::prime(L lambda) {
//   HotVertexSeq<Cs...> hot(*this);
//   hot.applyVertexLayout();
//   lambda(hot);
// }

template <typename... Ts> 
void VertexSeq<Ts...>::bindAll() {
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
  glBindVertexArray(m_vertexArrayObject);
}

template <typename... Ts> 
void VertexSeq<Ts...>::bindVAO() const {
  glBindVertexArray(m_vertexArrayObject);
}

template <typename... Ts> 
void VertexSeq<Ts...>::unbindVAO() const {
  glBindVertexArray(m_vertexArrayObject);
}


template <typename... Ts> 
void VertexSeq<Ts...>::unbindAll() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <typename... Ts> 
GLuint VertexSeq<Ts...>::nativeVertexHandle() const {
  return m_vertexHandle;
}

template <typename... Ts> 
GLuint VertexSeq<Ts...>::nativeIndexHandle() const {
  return m_indexHandle;
}

template <typename... Ts> 
GLuint VertexSeq<Ts...>::nativeVAOHandle() const {
  return m_vertexArrayObject;
}

template <typename... Ts> 
int VertexSeq<Ts...>::size() const {
  return (m_indexHandle == 0) ? m_vertexCount : m_indexCount;
}

template <typename... Ts> 
bool VertexSeq<Ts...>::isVertexLayoutActive() const {
  return m_layoutActive;
}

template <typename... Ts> 
VertexSeq<Ts...>::operator bool() const {
   return (m_vertexHandle != 0);
}

} // namespace lumina