namespace lumina {

template <typename... Cs>
HotMesh<Cs...>::HotMesh(Mesh& ref)
  : m_mesh(ref), vertex(ref.m_vertexCount), index(ref.m_indexCount) {
  // check if a mesh is already primed... if not, set primed marker
  if(Mesh::s_isPrimed) {
    logError(
      "[HotMesh] Attempt to prime a mesh while another is already primed!");
    throw GLException(
      "[HotMesh] Attempt to prime a mesh while another is already primed!");
  }
  Mesh::s_isPrimed = true;

  // bind all objects
  m_mesh.bindAll();

  // map vertex buffer
  vertex.m_buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

  // map index buffer, if it exists
  if(m_mesh.m_indexHandle != 0) {
    index.m_buffer
      = static_cast<int*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE));
  }

  // check for error
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[HotMesh] Error <",
             translateGLError(err),
             "> while creating HotMesh!");
    throw GLException("Error while creating HotMesh");
  }
}

// unmap and unbind all buffers
template <typename... Cs>
HotMesh<Cs...>::~HotMesh() {
  glUnmapBuffer(GL_ARRAY_BUFFER);
  if(index.m_buffer) {
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
  }

  // unmap buffers and VAO
  m_mesh.unbindAll();

  // check for error (remember: never evaar throw in dtor!)
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logWarning("[HotMesh] OpenGL error<", translateGLError(err), "> in "
      "HotMesh destructor!");
  }

  // remove primed marker
  Mesh::s_isPrimed = false;
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

template <typename... Cs>
void HotMesh<Cs...>::setPrimitiveType(PrimitiveType type) {
  switch(type) {
    case PrimitiveType::Point:
      m_mesh.m_primitiveType = GL_POINTS;
      break;
    case PrimitiveType::Triangle:
      m_mesh.m_primitiveType = GL_TRIANGLES;
      break;
    case PrimitiveType::TriangleStrip:
      m_mesh.m_primitiveType = GL_TRIANGLE_STRIP;
      break;
  }
}

}  // namespace lumina