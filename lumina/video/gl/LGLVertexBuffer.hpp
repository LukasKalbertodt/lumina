#pragma once

#include "../../config/BaseProxy.hpp"

#include <GL/glew.h>

#include <cstddef>
#include <memory>


namespace lumina {

class LGLVertexBuffer : public config::CommonBase {
public:
  // default constructor
  LGLVertexBuffer() : m_handle(0), m_vertexCount(0), m_vertexSize(0) {}

  // move constructor and move assignment operator
  LGLVertexBuffer(LGLVertexBuffer&& buf);
  LGLVertexBuffer& operator=(LGLVertexBuffer&& buf);

  // destructor
  ~LGLVertexBuffer();

  void create(std::size_t vertexCount,
              std::size_t vertexSize,
              bool dynamicBuffer = false);

  // GLuint GetHandle() { return m_handle; }

  std::size_t count() const { return m_vertexCount; }
  std::size_t vertexSize() const { return m_vertexSize; }
  std::size_t size() const { return m_vertexCount*m_vertexSize; }

  void copyData(const void* src, std::size_t size, std::size_t offset = 0);
  void* lock();
  void unlock();
  // void SetStreamSource();

private:
  GLuint m_handle;
  std::size_t m_vertexCount;
  std::size_t m_vertexSize;
};

typedef std::shared_ptr<LGLVertexBuffer> LGLVertexBufferPtr;

} // namespace lumina
