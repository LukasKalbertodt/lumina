namespace lumina {

/* Mesh constructors **********************************************************/
inline Mesh::Mesh()
  : m_vertexHandle(0),
    m_indexHandle(0),
    m_vertexArrayObject(0),
    m_vertexCount(0),
    m_indexCount(0),
    m_drawCount(0),
    m_primitiveType(GL_TRIANGLES) {}

// copy constructor and copy assignment operator
// inline Mesh::Mesh(const Mesh& copy);
// inline Mesh& operator=(const Mesh& copy);

// move constructor and move assignment operator
inline Mesh::Mesh(Mesh&& m)
  : m_vertexHandle(m.m_vertexHandle),
    m_indexHandle(m.m_indexHandle),
    m_vertexArrayObject(m.m_vertexArrayObject),
    m_vertexCount(m.m_vertexCount),
    m_indexCount(m.m_indexCount),
    m_drawCount(m.m_drawCount),
    m_primitiveType(m.m_primitiveType) {
  // reset values of m
  m.m_vertexHandle = 0;
  m.m_indexHandle = 0;
  m.m_vertexArrayObject = 0;
  m.m_vertexCount = 0;
  m.m_indexCount = 0;
  m.m_primitiveType = GL_TRIANGLES;
}
// inline Mesh& operator=(Mesh&& m);


/* Mesh methods ***************************************************************/
inline std::size_t Mesh::vertexCount() const { return m_vertexCount; }
inline std::size_t Mesh::indexCount() const { return m_indexCount; }
inline std::size_t Mesh::vertexSize() const { return m_vertexCount * 4; }
inline std::size_t Mesh::indexSize() const { return m_indexCount * 4; }

template <typename... Cs, typename L>
void Mesh::prime(L lambda) {
  HotMesh<Cs...> hot(*this);
  lambda(hot);
}

inline void Mesh::bindAll() {
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
  glBindVertexArray(m_vertexArrayObject);
}

inline void Mesh::unbindAll() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace lumina