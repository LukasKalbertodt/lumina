#include "Mesh.hpp"
#include <stdexcept>


namespace lumina {

bool Mesh::s_isPrimed = false;

void Mesh::sendData() {
  bindAll();
  glDrawArrays(m_primitiveType, 0, 3);
  unbindAll();
}

Mesh::~Mesh() {
  // glDelete* does nothing if second argument is 0
  glDeleteBuffers(1, &m_vertexHandle);
  glDeleteBuffers(1, &m_indexHandle);
  glDeleteVertexArrays(1, &m_vertexArrayObject);
}


void Mesh::create(int vertexCount, int indexCount) {
  // check if any other Mesh is primed
  if(s_isPrimed) {
    logError("[Mesh] Cannot execute 'create' while another Mesh is primed!");
    throw GLException(
      "[Mesh] Cannot execute 'create' while another Mesh is primed");
  }

  // check arguments
  if(vertexCount < 1 || indexCount < 0) {
    logError("[Mesh] Invalid 'create' arguments: vertexCount<",
             vertexCount, ">, indexCount<", indexCount, ">!");
    throw std::invalid_argument("[Mesh] Invalid 'create' arguments");
  }

  // save arguments
  m_vertexCount = vertexCount;
  m_indexCount = indexCount;

  // create and bind VAO
  glGenVertexArrays(1, &m_vertexArrayObject);
  glBindVertexArray(m_vertexArrayObject);

  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[Mesh] Error while creating VAO <", translateGLError(err), ">!");
    throw GLException("[Mesh] Error while creating VAO");
  }

  // create vertex buffer (generate, bind and allocate memory)
  glGenBuffers(1, &m_vertexHandle);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
  glBufferData(GL_ARRAY_BUFFER, vertexSize(), nullptr, GL_STATIC_DRAW);

  err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[Mesh] Error while creating vertex buffer <",
             translateGLError(err), ">!");
    throw GLException("[Mesh] Error while creating vertex buffer");
  }

  // create index buffer, if requested
  if(indexCount > 0) {
    glGenBuffers(1, &m_indexHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize(), nullptr, GL_STATIC_DRAW);
    
    err = glGetError();
    if(err != GL_NO_ERROR) {
      logError("[Mesh] Error while creating index buffer <",
               translateGLError(err), ">!");
      throw GLException("[Mesh] Error while creating index buffer");
    }
  }

  // unbind all buffers and VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

} // namespace lumina