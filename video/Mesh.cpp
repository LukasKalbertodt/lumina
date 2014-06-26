#include "Mesh.hpp"
#include "GLException.hpp"
#include "GLTools.hpp"
#include "../core/LuminaException.hpp"
// #include "../service/StaticLogger.hpp"

#include <limits>
#include <stdexcept>


namespace lumina {

bool Mesh::s_isPrimed = false;

void Mesh::sendData() {
  bindAll();
  // glDrawArrays(GL_TRIANGLE_STRIP, 0, 20);
  if(m_indexHandle == 0) {
    glDrawArrays(m_primitiveType, 0, m_drawCount);
  }
  else {
    // log("indexCOunt: ", m_indexCount);
    glDrawElements(m_primitiveType, m_indexCount, GL_UNSIGNED_INT, nullptr);
  }
  unbindAll();

  checkGLError("[Mesh] Error<", GLERR, "> while sending mesh data!");
}

Mesh::~Mesh() {
  // glDelete* does nothing if second argument is 0
  glDeleteBuffers(1, &m_vertexHandle);
  glDeleteBuffers(1, &m_indexHandle);
  glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::setupOpenGL() {
  static bool wasCalled = false;
  if(!wasCalled) {
    // configure primitive restart
    glPrimitiveRestartIndex(std::numeric_limits<unsigned int>::max());
    glEnable(GL_PRIMITIVE_RESTART);
    wasCalled = true;
  }
}


void Mesh::create(int vertexCount, int indexCount) {
  // check if mesh was already created
  if(m_vertexHandle != 0) {
    logError("[Mesh] You can create a mesh only once!");
    throw LogicEx("[Mesh] You can create a mesh only once!");
  }

  // check if any other Mesh is primed
  if(s_isPrimed) {
    logError("[Mesh] Cannot execute 'create' while another Mesh is primed!");
    throw LogicEx(
      "[Mesh] Cannot execute 'create' while another Mesh is primed");
  }

  // check arguments
  if(vertexCount < 1 || indexCount < 0) {
    logError("[Mesh] Invalid 'create' arguments: vertexCount<",
             vertexCount, ">, indexCount<", indexCount, ">!");
    throw InvalidArgEx("[Mesh] Invalid 'create' arguments");
  }

  // save arguments
  m_vertexCount = vertexCount;
  m_indexCount = indexCount;

  // create and bind VAO
  glGenVertexArrays(1, &m_vertexArrayObject);
  glBindVertexArray(m_vertexArrayObject);


  checkGLError("[Mesh] Error while creating VAO <", GLERR, ">!");

  // create vertex buffer (generate, bind and allocate memory)
  glGenBuffers(1, &m_vertexHandle);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
  glBufferData(GL_ARRAY_BUFFER, vertexSize(), nullptr, GL_STATIC_DRAW);

  checkGLError("[Mesh] Error while creating vertex buffer <", GLERR, ">!");

  // create index buffer, if requested
  if(indexCount > 0) {
    glGenBuffers(1, &m_indexHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize(), nullptr, GL_STATIC_DRAW);

    checkGLError("[Mesh] Error while creating index buffer <", GLERR, ">!");
  }

  // unbind all buffers and VAO
  unbindAll();
}

} // namespace lumina