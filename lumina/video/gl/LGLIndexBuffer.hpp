#pragma once

#include "../../config/BaseProxy.hpp"

#include <GL/glew.h>
#include <memory>
#include <cstddef>

namespace lumina {

class LGLIndexBuffer : public config::CommonBase {
public:
  LGLIndexBuffer() : m_handle(0), m_indexCount(0) {}
  ~LGLIndexBuffer();

  void create(std::size_t indexCount, bool dynamicBuffer = false);

  std::size_t count() const { return m_indexCount; }
  std::size_t size() const { return m_indexCount * 4; }

  void setData(const void* src, std::size_t size, std::size_t offset = 0);
  void* lock();
  void unlock();
    // void SetIndices();

private : 
  GLuint m_handle;
  std::size_t m_indexCount;
};

typedef std::shared_ptr<LGLIndexBuffer> LGLIndexBufferPtr;

} // namespace lumina
