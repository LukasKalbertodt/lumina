#include "RenderBuffer.hpp"

namespace lumina {

bool RenderBuffer::s_primed = false;

static GLenum renderBufferGLType(RenderBufferType type) {
  switch(type) {
    case RenderBufferType::Depth32:
      return GL_DEPTH_COMPONENT32;
    case RenderBufferType::Depth16:
      return GL_DEPTH_COMPONENT16;
    case RenderBufferType::Depth24Stencil8:
      return GL_DEPTH24_STENCIL8;
  }
}

void RenderBuffer::create(Vec2i size, RenderBufferType type) {
  // check if another renderbuffer is bound (that should never occur)
  if(s_primed) {
    logThrowGL("[FrameBuffer] Cannot add a default buffer while another "
               "renderbuffer is currently bound!");
  }

  // set primed lock 
  s_primed = true;

  // generate new renderbuffer with the given type
  glGenRenderbuffers(1, &m_handle);
  glBindRenderbuffer(GL_RENDERBUFFER, m_handle);

  glRenderbufferStorage(GL_RENDERBUFFER, renderBufferGLType(type),
                        size.x, size.y);

  checkGLError("[FrameBuffer] Error<", GLERR,
               "> while creating default renderbuffer!");

  // save params
  m_type = type;
  m_size = size;

  // reset primed lock
  s_primed = false;
}

} // namespace lumina