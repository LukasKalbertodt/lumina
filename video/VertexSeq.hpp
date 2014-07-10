#pragma once

#include "VertexSeq.fpp"
#include "HotVertexSeq.fpp"
#include "HotProgram.fpp"
#include "GLObject.hpp"
#include "../config/BaseProxy.hpp"

#include <GL/glew.h>
#include <cstddef>
#include <memory>
#include <iostream>


namespace lumina {
// =============================================================================
// Definition of VertexSeq
// =============================================================================
/**
* \brief Represents a geometry mesh
* VertexSeq represents a collection of vertices with arbitrary attributes, which may
* be indexed. It uses an OpenGL vertex buffer and an optional index buffer. 
* The typical creation cycle is: 
* * Creating a new instance of VertexSeq (which is useless on it's own)
* * Call `create` to create the underlying data structures
* * Call `prime` to obtain a HotVertexSeq (the VertexSeq needs to be created first)
*/
class VertexSeq : public GLObject {
public:
  // default constructor
  VertexSeq();

  // VertexSeq(int vertexCount);
  // VertexSeq(int vertexCount, int indexCount);

  // copy constructor and copy assignment operator
  VertexSeq(const VertexSeq& copy);
  VertexSeq &operator=(const VertexSeq &copy);

  // move constructor and move assignment operator
  VertexSeq(VertexSeq&& m);
  VertexSeq& operator=(VertexSeq&& m);

  // destructor
  ~VertexSeq();

  void create(uint16_t vertexSize,
              uint32_t vertexCount,
              uint32_t indexCount = 0);
  template <typename... Cs, typename L> void prime(L lambda);


private:
  GLuint m_vertexHandle;
  GLuint m_indexHandle;
  GLuint m_vertexArrayObject;
  uint32_t m_vertexCount;
  uint32_t m_indexCount;
  uint16_t m_vertexSize;
  // std::size_t m_drawCount;

  void bindAll();
  void unbindAll();

  static bool s_isPrimed;

  static void setupOpenGL();

  template <typename... Cs> friend class HotVertexSeq;
  friend HotProgram;
};

} // namespace lumina

// include out of line definitions
#include "VertexSeq.tpp"