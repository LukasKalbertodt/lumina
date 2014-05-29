namespace lumina {

/* Mesh constructors **********************************************************/
inline Mesh::Mesh()
  : m_vertexHandle(0),
    m_indexHandle(0),
    m_vertexArrayObject(0),
    m_vertexCount(0),
    m_indexCount(0),
    m_primitiveType(GL_TRIANGLES) {}

// copy constructor and copy assignment operator
// Mesh::Mesh(const Mesh& copy);
// Mesh& operator=(const Mesh& copy);

// // move constructor and move assignment operator
// Mesh::Mesh(Mesh&& m);
// Mesh& operator=(Mesh&& m);


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