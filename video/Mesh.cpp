#include "Mesh.hpp"


namespace lumina {

void Mesh::sendData() {
  // bindVAO();
  // bindVBO();
  glDrawArrays(m_primitiveType, 0, 3);
}

Mesh::~Mesh() {
  // glDelete* does nothing if second argument is 0
  glDeleteBuffers(1, &m_vertexHandle);
  glDeleteBuffers(1, &m_indexHandle);
  glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::create(int vertexCount) {
  m_vertexCount = vertexCount;

  // Create vertex buffer
  glGenBuffers(1, &m_vertexHandle);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);

  glBufferData(GL_ARRAY_BUFFER, vertexSize(), nullptr, GL_STATIC_DRAW);

  // Check for error
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[Mesh] Unable to create vertex buffer <",
             translateGLError(err),
             "> !");
    throw LGLException("Unable to create vertex buffer");
  }
}

void Mesh::create(int vertexCount, int indexCount) {
  // create vertex buffer
  create(vertexCount);

  m_indexCount = indexCount;

  // TODO: create index buffer
}


// void Mesh::fillVertexData(const void* src,
//                               std::size_t size,
//                               std::size_t offset) {
//   // bind buffer and copy data
//   bindVBO();
//   glBufferSubData(GL_ARRAY_BUFFER, offset, size, src);

//   // check for errors
//   auto err = glGetError();
//   if(err != GL_NO_ERROR) {
//     logError("[Mesh] Error <", err, "> while copying data into buffer!");
//     throw LGLException("Error while copying data into buffer");
//   }
// }

void Mesh::bindVAO() {
  // create new if none was created so far
  if(m_vertexArrayObject == 0) {
    glGenVertexArrays(1, &m_vertexArrayObject);
  }
  glBindVertexArray(m_vertexArrayObject);
}



void Mesh::bindVBO() {
  if(m_vertexHandle == 0) {
    logError("[Mesh] Attempt to bind VBO, but it was never created!");
    throw LGLException("Attempt to bind VBO, but it was never created");
  }
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
}

} // namespace lumina