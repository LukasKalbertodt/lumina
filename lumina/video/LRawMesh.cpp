#include "LRawMesh.hpp"

#include "../core/LGLException.hpp"  

namespace lumina {

LRawMesh::~LRawMesh() {
  // glDelete* does nothing if second argument is 0
  glDeleteBuffers(1, &m_vertexHandle);
  glDeleteBuffers(1, &m_indexHandle);
  glDeleteVertexArrays(1, &m_vertexArrayObject);
}


void LRawMesh::createVertexBuffer(std::size_t vertexCount) {
  // assign new values  
  m_vertexCount = vertexCount;

  // Create buffer
  glGenBuffers(1, &m_vertexHandle);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);

  glBufferData(GL_ARRAY_BUFFER, size(), nullptr, GL_STATIC_DRAW);

  // Check for error
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[LRawMesh] Unable to create vertex buffer!");
    throw LGLException("Unable to create vertex buffer");
  }
}

void LRawMesh::setVertexLayout(LVertexLayout layout) {
  m_vertexLayout = layout;
  bindVAO();
  bindVBO();
  m_vertexLayout.apply();

  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[LRawMesh] Error while applying vertex layout!");
    throw LGLException("Error while applying vertex layout");
  }
}


void LRawMesh::fillVertexData(const void* src,
                              std::size_t size,
                              std::size_t offset) {
  // bind buffer and copy data
  bindVBO();
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, src);

  // check for errors
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[LRawMesh] Error while copying data into buffer!");
    throw LGLException("Error while copying data into buffer");
  }
}

void LRawMesh::bindVAO() {
  if(m_vertexArrayObject != 0) {
    glGenVertexArrays(1, &m_vertexArrayObject);
  }
  glBindVertexArray(m_vertexArrayObject);
}

void LRawMesh::bindVBO() {
  if(m_vertexHandle == 0) {
    logError("[LRawMesh] Attempt to bind VBO, but it was never created!");
    throw LGLException("Attempt to bind VBO, but it was never created");
  }
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
}

} // namespace lumina