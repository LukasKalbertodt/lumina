#pragma once

#include "../config/BaseProxy.hpp"
#include "LGLTools.hpp"
#include "../core/LGLException.hpp"  
#include "LVertexLayout.hpp"

#include <GL/glew.h>
#include <cstddef>
#include <memory>


namespace lumina {

template <typename...>
class HotMesh;

class LMesh : public config::CommonBase {
public:
  // default constructor
  LMesh()
    : m_vertexHandle(0),
      m_indexHandle(0),
      m_vertexArrayObject(0),
      m_vertexCount(0),
      m_indexCount(0) {}

  LMesh(int vertexCount) : LMesh() {
    create(vertexCount);
  }
  LMesh(int vertexCount, int indexCount) : LMesh() {
    create(vertexCount, indexCount);
  }

  // copy constructor and copy assignment operator
  LMesh(const LMesh& copy);
  LMesh& operator=(const LMesh& copy);


  // move constructor and move assignment operator
  LMesh(LMesh&& m);
  LMesh& operator=(LMesh&& m);

  // destructor
  ~LMesh();

  void create(int vertexCount);
  void create(int vertexCount, int indexCount);
  template <typename... Cs, typename L>
  void apply(L lambda);


protected:
  GLuint m_vertexHandle;
  GLuint m_indexHandle;
  GLuint m_vertexArrayObject;
  std::size_t m_vertexCount;
  std::size_t m_indexCount;

  std::size_t vertexCount() const { return m_vertexCount; }
  std::size_t indexCount() const { return m_indexCount; }
  std::size_t vertexSize() const { return m_vertexCount * 4; }
  std::size_t indexSize() const { return m_indexCount * 4; }

  void fillVertexData(const void* src,
                      std::size_t size,
                      std::size_t offset = 0);

  void bindVAO();
  void bindVBO();
};

template <typename... Cs>
class HotMesh : public LMesh {
public:
  // delete copy and move constructors to avoid copys
  HotMesh(const HotMesh&) = delete;
  HotMesh& operator=(const HotMesh&) = delete;
  HotMesh(HotMesh&&) = delete;
  HotMesh& operator==(HotMesh&&) = delete;

  // use functions of base class
  using LMesh::fillVertexData;
  void applyVertexLayout();

private:
};


template <typename... Cs, typename L>
void LMesh::apply(L lambda) {
  bindVAO();
  bindVBO();

  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[LMesh] Error <",
             translateGLError(err),
             "> while binding mesh!");
    throw LGLException("Error while binding mesh");
  }

  lambda(*static_cast<HotMesh<Cs...>*>(this));
}

template <typename... Cs>
void HotMesh<Cs...>::applyVertexLayout() {
  internal::applyLayoutImpl<0,
                            internal::LayoutTypes<Cs...>::stride,
                            0,
                            sizeof(Cs)...>();
}

} // namespace lumina
