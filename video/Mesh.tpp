namespace lumina {

/* Mesh constructors **********************************************************/
inline Mesh::Mesh()
  : m_vertexHandle(0),
    m_indexHandle(0),
    m_vertexArrayObject(0),
    m_vertexCount(0),
    m_indexCount(0),
    m_primitiveType(GL_TRIANGLES) {}

// protected reference constructor
inline Mesh::Mesh(Mesh& ref) 
  : m_vertexHandle(ref.m_vertexHandle),
    m_indexHandle(ref.m_indexHandle),
    m_vertexArrayObject(ref.m_vertexArrayObject),
    m_vertexCount(ref.m_vertexCount),
    m_indexCount(ref.m_indexCount),
    m_primitiveType(ref.m_primitiveType) {}

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

template <typename... Cs, typename L>
void Mesh::prime(L lambda) {
  HotMesh<Cs...> hot(*this);
  lambda(hot);
}

/* HotMesh methods ************************************************************/
template <typename... Cs>
HotMesh<Cs...>::HotMesh(Mesh& ref)
  : Mesh(ref), vertex(ref.m_vertexCount), index(ref.m_indexCount) {
  // check if a mesh is already primed... if not, set primed marker
  if(Mesh::s_isPrimed) {
    logError("[Mesh] Attempt to prime a mesh while another is already primed!");
    throw GLException(
      "[Mesh] Attempt to prime a mesh while another is already primed!");
  }
  Mesh::s_isPrimed = true;

  // bind all objects
  bindAll();

  // map vertex buffer
  vertex.buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

  // map index buffer, if it exists
  if(m_indexHandle != 0) {
    index.m_buffer
      = static_cast<int*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE));
  }

  // check for error
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[Mesh] Error <",
             translateGLError(err),
             "> while creating HotMesh!");
    throw GLException("Error while creating HotMesh");
  }
}

// set handles to 0 so ~Mesh won't delete them (dirty hack...)
template <typename... Cs>
HotMesh<Cs...>::~HotMesh() {
  this->m_vertexHandle = 0;
  this->m_indexHandle = 0;
  this->m_vertexArrayObject = 0;

  glUnmapBuffer(GL_ARRAY_BUFFER);
  if(index.m_buffer) {
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
  }

  // unmap buffers and VAO
  unbindAll();

  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logWarning("[HotMesh] OpenGL error<", translateGLError(err), "> in "
      "HotMesh destructor!");
  }

  // remove primed marker
  Mesh::s_isPrimed = false;
}

inline void Mesh::bindAll() {
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
  glBindVertexArray(m_vertexArrayObject);
}

inline void Mesh::unbindAll() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <typename... Cs>
void HotMesh<Cs...>::applyVertexLayout() {
  internal::applyLayoutImpl<0, internal::LayoutTypes<Cs...>::stride,
                            0, sizeof(Cs)...>();
  
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[HotMesh] Error<", translateGLError(err), "> while applying "
      "vertex layout!");
    throw GLException("[HotMesh] Error while applying vertex layout");
  }
}



} // namespace lumina