#include "LGLVertexBuffer.hpp"

#include "../../core/LGLException.hpp"  

namespace lumina {

LGLVertexBuffer::LGLVertexBuffer(LGLVertexBuffer&& buf)
  : m_handle(buf.m_handle),
    m_vertexCount(buf.m_vertexCount),
    m_vertexSize(buf.m_vertexSize) {
  // reset values of temporary object
  buf.m_handle      = 0;
  buf.m_vertexCount = 0;
  buf.m_vertexSize  = 0;
}

LGLVertexBuffer& LGLVertexBuffer::operator=(LGLVertexBuffer&& buf) {
  // copy values from temporary object
  m_handle      = buf.m_handle;
  m_vertexCount = buf.m_vertexCount;
  m_vertexSize  = buf.m_vertexSize;

  // reset values of temporary object
  buf.m_handle      = 0;
  buf.m_vertexCount = 0;
  buf.m_vertexSize  = 0;

  return *this;
}


LGLVertexBuffer::~LGLVertexBuffer() {
  // glDeleteBuffers does nothing if second argument is 0
  glDeleteBuffers(1, &m_handle);
  // driver->ClearVertexLayout(m_handle);
}

void LGLVertexBuffer::create(std::size_t vertexCount,
                             std::size_t vertexSize,
                             bool dynamicBuffer) {
  // assign new values  
  m_vertexCount = vertexCount;
  m_vertexSize = vertexSize;

  // Create buffer
  glGenBuffers(1, &m_handle);
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);

  GLenum usage = dynamicBuffer ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
  glBufferData(GL_ARRAY_BUFFER, size(), nullptr, usage);

  // Check for error
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[GLVertexBuffer] Unable to create vertex buffer!");
    throw LGLException("Unable to create vertex buffer!");
  }
}

void LGLVertexBuffer::copyData(const void* src,
                               std::size_t size,
                               std::size_t offset) {
  // bind buffer and copy data
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, src);

  // check for errors
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[GLVertexBuffer] Error while copying data into buffer!");
    throw LGLException("Error while copying data into buffer");
  }
}

void* LGLVertexBuffer::lock() {
  // bind buffer
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);

  // configurate access mode and try to map buffer
  GLbitfield mode = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
  auto* ptr = glMapBufferRange(GL_ARRAY_BUFFER, 0, size(), mode);

  // if ptr is nullptr, an error occured
  if(!ptr) {
    logError("[GLVertexBuffer] Could not lock buffer!");
    throw LGLException("Could not lock buffer");
  }
  return ptr;
}

void LGLVertexBuffer::unlock() {
  // bind and unmap buffer
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  glUnmapBuffer(GL_ARRAY_BUFFER);

  // error checking
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logWarning("[GLVertexBuffer] Tried to unmap a buffer which is not mapped");
  }
}

// void LGLVertexBuffer::SetStreamSource()
// {
//   CGLDriver* driver = static_cast<CGLDriver*>(m_dev->GetVideoDriver());
//   driver->SetVertexBuffer(m_handle);
// }

}
