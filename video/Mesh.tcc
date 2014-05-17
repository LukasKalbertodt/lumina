namespace lumina {

inline Mesh::Mesh()
  : m_vertexHandle(0),
    m_indexHandle(0),
    m_vertexArrayObject(0),
    m_vertexCount(0),
    m_indexCount(0),
    m_primitiveType(GL_TRIANGLES) {}

inline Mesh::Mesh(int vertexCount) : Mesh() { 
  create(vertexCount); 
}

inline Mesh::Mesh(int vertexCount, int indexCount) : Mesh() {
  create(vertexCount, indexCount);
}

// copy constructor and copy assignment operator
// Mesh::Mesh(const Mesh& copy);
// Mesh& operator=(const Mesh& copy);

// // move constructor and move assignment operator
// Mesh::Mesh(Mesh&& m);
// Mesh& operator=(Mesh&& m);


inline std::size_t Mesh::vertexCount() const { return m_vertexCount; }
inline std::size_t Mesh::indexCount() const { return m_indexCount; }
inline std::size_t Mesh::vertexSize() const { return m_vertexCount * 4; }
inline std::size_t Mesh::indexSize() const { return m_indexCount * 4; }

inline void Mesh::setPrimitiveType(PrimitiveType type) {
  switch(type) {
    case PrimitiveType::Point:
      m_primitiveType = GL_POINTS;
      break;
    case PrimitiveType::Triangle:
      m_primitiveType = GL_TRIANGLES;
      break;
    case PrimitiveType::TriangleStrip:
      m_primitiveType = GL_TRIANGLE_STRIP;
      break;
  }
}


template <typename... Cs>
HotMesh<Cs...>::HotMesh(Mesh& ref) : vertex(ref.m_vertexCount) {
  this->m_vertexHandle = ref.m_vertexHandle;
  this->m_indexHandle = ref.m_indexHandle;
  this->m_vertexArrayObject = ref.m_vertexArrayObject;
  this->m_vertexCount = ref.m_vertexCount;
  this->m_indexCount = ref.m_indexCount;

  bindVAO();
  bindVBO();

  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[Mesh] Error <",
             translateGLError(err),
             "> while creating hot mesh!");
    throw LGLException("Error while creating hot mesh");
  }

  GLbitfield mode = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
  vertex.m_buf = glMapBufferRange(GL_ARRAY_BUFFER, 0, vertexSize(), mode);
}

}