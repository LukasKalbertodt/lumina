#include "VertexSeq.hpp"
#include "GLException.hpp"
#include "GLTools.hpp"
#include "../core/LuminaException.hpp"
#include "HotVertexSeq.hpp"

#include <limits>
#include <stdexcept>


namespace lumina {

bool VertexSeq::s_isPrimed = false;

VertexSeq::~VertexSeq() {
  // glDelete* does nothing if second argument is 0
  glDeleteBuffers(1, &m_vertexHandle);
  glDeleteBuffers(1, &m_indexHandle);
  glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void VertexSeq::setupOpenGL() {
  static bool wasCalled = false;
  if(!wasCalled) {
    // configure primitive restart
    glPrimitiveRestartIndex(std::numeric_limits<unsigned int>::max());
    glEnable(GL_PRIMITIVE_RESTART);
    wasCalled = true;
  }
}


void VertexSeq::create(uint16_t vertexSize,
                       uint32_t vertexCount,
                       uint32_t indexCount) {
  // check if vertex buffer was already created
  if(m_vertexHandle != 0) {
    logError("[VertexSeq] You can create a VertexSeq only once!");
    throw LogicEx("[VertexSeq] You can create a VertexSeq only once!");
  }

  // check if any other VertexSeq is primed
  if(s_isPrimed) {
    logError(
      "[VertexSeq] Cannot execute 'create' while another VertexSeq is primed!");
    throw LogicEx(
      "[VertexSeq] Cannot execute 'create' while another VertexSeq is primed");
  }

  // check arguments
  if(vertexCount < 1) {
    logError("[VertexSeq] Invalid 'create' arguments: vertexCount<",
             vertexCount, ">, indexCount<", indexCount, ">!");
    throw InvalidArgEx("[VertexSeq] Invalid 'create' arguments");
  }

  // save arguments
  m_vertexCount = vertexCount;
  m_vertexSize = vertexSize;
  m_indexCount = indexCount;

  // create and bind VAO
  glGenVertexArrays(1, &m_vertexArrayObject);
  glBindVertexArray(m_vertexArrayObject);


  checkGLError("[VertexSeq] Error while creating VAO <", GLERR, ">!");

  // create vertex buffer (generate, bind and allocate memory)
  glGenBuffers(1, &m_vertexHandle);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexHandle);
  glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexCount * sizeof(GLfloat),
               nullptr, GL_STATIC_DRAW);

  checkGLError("[VertexSeq] Error while creating vertex buffer <", GLERR, ">!");

  // create index buffer, if requested
  if(indexCount > 0) {
    glGenBuffers(1, &m_indexHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLint),
                 nullptr, GL_STATIC_DRAW);

    checkGLError("[VertexSeq] Error while creating index buffer <", GLERR, ">!");
  }

  // unbind all buffers and VAO
  unbindAll();
}

void VertexSeq::prime(std::function<void(HotVertexSeq<>&)> func) {
  HotVertexSeq<> hot(*this);
  func(hot);
}


} // namespace lumina