#include "LGLIndexBuffer.hpp"

#include "../../core/LGLException.hpp"

namespace lumina {


// LGLIndexBuffer::~LGLIndexBuffer()
// {
//   glDeleteBuffers(1, &m_handle);
//   if(m_dev->GetVideoDriver())
//     m_dev->GetVideoDriver()->UntrackResource(this);
// }

void LGLIndexBuffer::create(std::size_t indexCount, bool dynamicBuffer) {
  m_indexCount = indexCount;

  // create buffer
  glGenBuffers(1, &m_handle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);

  GLenum usage = dynamicBuffer ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size(), nullptr, usage);

  // check for errors
  GLenum err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[GLIndexBuffer] Unable to create index buffer!");
    throw LGLException("Unable to create index buffer!");
  }
}

void LGLIndexBuffer::setData(const void* src,
                             std::size_t size,
                             std::size_t offset) {
  // bind buffer and copy data
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, src);

  // check for errors
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[GLIndexBuffer] Error while copying data into buffer!");
    throw LGLException("Error while copying data into buffer");
  }
}

void* LGLIndexBuffer::lock() {
  // bind buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);

  // configurate access mode and try to map buffer
  GLbitfield mode = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
  auto* ptr = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, size(), mode);

  // if ptr is nullptr, an error occured
  if(!ptr) {
    logError("[GLIndexBuffer] Could not lock buffer!");
    throw LGLException("Could not lock buffer");
  }
  return ptr;
}

void LGLIndexBuffer::unlock() {
  // bind buffer and try to unmap it
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
  glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

  // error checking
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logWarning("[GLIndexBuffer] Tried to unmap a buffer which is not mapped");
  }
}

// void LGLIndexBuffer::SetIndices()
// {
//   CGLDriver* driver = static_cast<CGLDriver*>(m_dev->GetVideoDriver());
//   driver->SetIndexBuffer(m_handle);
// }

} // namespace lumina
