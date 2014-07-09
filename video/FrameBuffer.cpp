#include "FrameBuffer.hpp"

namespace lumina {

void FrameBuffer::create() {
  glGenFramebuffers(1, &m_handle);

  // check error
  checkGLError("[FrameBuffer] Error<", GLERR, "> while creating frame buffer!");
}


}