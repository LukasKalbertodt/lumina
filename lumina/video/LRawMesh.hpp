#pragma once

#include "../config/BaseProxy.hpp"
#include "LVertexLayout.hpp"

#include <GL/glew.h>

#include <cstddef>
#include <memory>


namespace lumina {

class LRawMesh : public config::CommonBase {
public:
  // default constructor
  LRawMesh()
    : m_vertexHandle(0),
      m_indexHandle(0),
      m_vertexArrayObject(0),
      m_vertexCount(0),
      m_indexCount(0) {}

  // copy constructor and copy assignment operator
  // TODO

  // move constructor and move assignment operator
  LRawMesh(LRawMesh&& buf);
  LRawMesh& operator=(LRawMesh&& buf);

  // destructor
  ~LRawMesh();

  void createVertexBuffer(std::size_t vertexCount);
  void setVertexLayout(LVertexLayout layout);

  GLuint getVertexHandle() { return m_vertexHandle; }
  GLuint getIndexHandle() { return m_indexHandle; }

  std::size_t vertexCount() const { return m_vertexCount; }
  std::size_t indexCount() const { return m_indexCount; }
  std::size_t size() const { return m_vertexCount * 4; }

  void fillVertexData(const void* src,
                      std::size_t size,
                      std::size_t offset = 0);
  // void copyVertexData(const void* src,
  //                     std::size_t size,
  //                     std::size_t offset = 0);
  // void* lock();
  // void unlock();
  // void SetStreamSource();

private:
  GLuint m_vertexHandle;
  GLuint m_indexHandle;
  GLuint m_vertexArrayObject;
  std::size_t m_vertexCount;
  std::size_t m_indexCount;
  LVertexLayout m_vertexLayout;

  void createVAO();
};

} // namespace lumina
