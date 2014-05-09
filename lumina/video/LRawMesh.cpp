#include "LRawMesh.hpp"

#include "../core/LGLException.hpp"  

namespace lumina {

LRawMesh::~LRawMesh() {
  // glDeleteBuffers does nothing if second argument is 0
  glDeleteBuffers(1, &m_vertexHandle);
  glDeleteBuffers(1, &m_indexHandle);
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
  glBindVertexArray(m_vertexArrayObject);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
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
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, src);

  // check for errors
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[LRawMesh] Error while copying data into buffer!");
    throw LGLException("Error while copying data into buffer");
  }
}

void LRawMesh::createVAO() {
  if(m_vertexArrayObject != 0) {
    glGenVertexArrays(1, &m_vertexArrayObject);
  }
}


} // namespace lumina