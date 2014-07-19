#include "FrameBuffer.hpp"
#include "HotFrameBuffer.hpp"

namespace lumina {

bool FrameBuffer::s_isPrimed = false;

void FrameBuffer::create() {
  // generate framebuffer
  glGenFramebuffers(1, &m_handle);

  // prepare attachment points (TODO: Don't use glGet here directly)
  GLint numBuffers = 0;
  glGetIntegerv(GL_MAX_DRAW_BUFFERS, &numBuffers);
  m_attachments.resize(numBuffers);

  // check error
  checkGLError("[FrameBuffer] Error<", GLERR, "> while creating frame buffer!");
}

void FrameBuffer::updateState() {
  // check if update is really needed
  if(!m_needsUpdate) {
    return;
  }

  // prepare array for glDrawBuffers
  std::vector<GLenum> drawBuffers(m_attachments.size(), GL_NONE);

  // check each attachment and attach it if its non-zero
  for(int i = 0; i < m_attachments.size(); ++i) {
    auto& tex = m_attachments[i];
    if(tex != 0) {
      glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, tex, 0);
      drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
  }

  // specify which attachment points to use
  glDrawBuffers(m_attachments.size(), drawBuffers.data());

  // check for errors
  checkGLError("[FrameBuffer] Error<", GLERR, "> while updating state!");
}

void FrameBuffer::prime(std::function<void(HotFrameBuffer&)> func) {
  if(s_isPrimed) {
    logThrowGL(
      "[FrameBuffer] Cannot prime while another FrameBuffer is primed!");
  }

  // create hot framebuffer
  HotFrameBuffer hot(*this);

  func(hot);

  // check errors
  checkGLError("[FrameBuffer] Error<", GLERR, "> while priming!");
}

}