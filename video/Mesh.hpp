#pragma once

#include "Mesh.fpp"
#include "HotMesh.fpp"
#include "GLObject.hpp"
#include "../config/BaseProxy.hpp"

#include <GL/glew.h>
#include <cstddef>
#include <memory>
#include <iostream>


namespace lumina {
// =============================================================================
// Definition of Mesh and HotMesh
// =============================================================================
/**
* \brief Represents a geometry mesh
* Mesh represents a collection of vertices with arbitrary attributes, which may
* be indexed. It uses an OpenGL vertex buffer and an optional index buffer. 
* The typical creation cycle is: 
* * Creating a new instance of Mesh (which is useless on it's own)
* * Call `create` to create the underlying data structures
* * Call `prime` to obtain a HotMesh (the Mesh needs to be created first)
*/
class Mesh : public GLObject {
public:
  // default constructor
  Mesh();

  // Mesh(int vertexCount);
  // Mesh(int vertexCount, int indexCount);

  // copy constructor and copy assignment operator
  Mesh(const Mesh& copy);
  Mesh &operator=(const Mesh &copy);

  // move constructor and move assignment operator
  Mesh(Mesh&& m);
  Mesh& operator=(Mesh&& m);

  // destructor
  ~Mesh();

  void create(int vertexCount, int indexCount = 0);
  template <typename... Cs, typename L> void prime(L lambda);

  // tmp
  void sendData();


private:
  GLuint m_vertexHandle;
  GLuint m_indexHandle;
  GLuint m_vertexArrayObject;
  std::size_t m_vertexCount;
  std::size_t m_indexCount;
  std::size_t m_drawCount;
  GLenum m_primitiveType;

  std::size_t vertexCount() const;
  std::size_t indexCount() const;
  std::size_t vertexSize() const;
  std::size_t indexSize() const;

  void bindAll();
  void unbindAll();

  static bool s_isPrimed;

  static void setupOpenGL();

  template <typename... Cs> friend class HotMesh;
};

} // namespace lumina

// include out of line definitions
#include "Mesh.tpp"