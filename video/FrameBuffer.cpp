#include "FrameBuffer.hpp"
#include "HotFrameBuffer.hpp"

namespace lumina {
namespace internal {

bool FrameBufferInterface::s_isPrimed = false;

void UserFrameBuffer::create() {
  // generate framebuffer
  glGenFramebuffers(1, &m_handle);

  // prepare attachment points (TODO: Don't use glGet here directly)
  GLint numBuffers = 0;
  glGetIntegerv(GL_MAX_DRAW_BUFFERS, &numBuffers);
  m_colorAtts.resize(numBuffers);

  // check error
  checkGLError("[FrameBuffer] Error<", GLERR, "> while creating frame buffer!");
}

void UserFrameBuffer::updateState() {
  // check if update is really needed
  if(!m_needsUpdate) {
    return;
  }

  // prepare array for glDrawBuffers
  std::vector<GLenum> drawBuffers(m_colorAtts.size(), GL_NONE);

  // check each attachment and attach it if its non-zero
  for(int i = 0; i < m_colorAtts.size(); ++i) {
    auto& tex = m_colorAtts[i];
    if(tex.handle != 0) {
      glFramebufferTexture(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0 + i,
                           tex.handle, 0);
      drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
  }

  // specify which attachment points to use
  glDrawBuffers(m_colorAtts.size(), drawBuffers.data());

  // check for errors
  checkGLError("[FrameBuffer] Error<", GLERR, "> while updating state!");

  // reset flag
  m_needsUpdate = false;
}

void UserFrameBuffer::prime(std::shared_ptr<FrameBufferInterface> fb,
                            std::function<void(HotFrameBuffer&)> func) {
  if(s_isPrimed) {
    logThrowGL(
      "[FrameBuffer] Cannot prime while another FrameBuffer is primed!");
  }

  // bind to context and update state
  bind();
  updateState();

  // check framebuffer status and GL errors
  auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(status != GL_FRAMEBUFFER_COMPLETE) {
    // log error message
    logError("[FrameBuffer] Incomplete framebuffer status<", status, 
             "> while priming! -->");
    
    // print additional information about the error
    switch(status) {
      case GL_FRAMEBUFFER_UNDEFINED:
        logError("[FrameBuffer] The default framebuffer does not exist...");
        break;
      case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        logError("[FrameBuffer] At least one attachment is incomplete...");
        break;
      case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        logError("[FrameBuffer] No image is attached to the framebuffer...");
        break;
      case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        logError("[FrameBuffer] DrawBuffer is incorrect (internal error)...");
        break;
      case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        logError("[FrameBuffer] Read buffer has not attachment point...");
        break;
      case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        logError("[FrameBuffer] Not all images have the same number of "
                  "mutisample samples...");
        break;
      case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
        logError("[FrameBuffer] Layered images do not fit together...");
        break;
      case GL_FRAMEBUFFER_UNSUPPORTED:
        logError(
          "[FrameBuffer] Combination of attached images is not supported...");
        break;
      case 0:
        logError("[FrameBuffer] An internal error occured...");
        break;
      default:
        logError("[FrameBuffer] Unknown Error... ");
    }

    // throw exception
    throw GLException(
      "[FrameBuffer] Incomplete framebuffer status while priming!");
  }
  checkGLError("[FrameBuffer] Error<", GLERR, "> while priming!");

  // create HotFB and call func
  HotFrameBuffer hot(fb);
  func(hot);

  // unbind and check errors
  unbind();
  checkGLError("[FrameBuffer] Error<", GLERR, "> after priming!");
}

void UserFrameBuffer::attachColor(int index, const Tex2D& tex) {
  // check index
  if(index >= m_colorAtts.size()) {
    logAndThrow<OutOfRangeEx>("[FrameBuffer] Attachment-point-index<", index, 
                              "> higher than the maximum number of available "
                              "attachment points<", m_colorAtts.size(), ">!");
  }

  // check texture format
  auto f = tex.getFormat();
  if(f == TexFormat::D16 || f == TexFormat::D32 || f == TexFormat::D24S8) {
    logAndThrow<InvalidArgEx>("[FrameBuffer] You can not attach a texture "
                              "with depth or stencil format to a color "
                              "attachment point!");
  }

  // assign values if the values are distinct
  auto& m_point = m_colorAtts[index];
  if(m_point.handle != tex.nativeHandle()) {
    m_point.handle = tex.nativeHandle();
    m_point.format = f;
    m_needsUpdate = true;
  }
}

int UserFrameBuffer::countAttachments() {
  int count = 0;
  for(auto& point : m_colorAtts) {
    if(point.handle != 0) {
      count++;
    }
  }
  return count;
}





void DefaultFrameBuffer::prime(std::shared_ptr<FrameBufferInterface> fb,
                            std::function<void(HotFrameBuffer&)> func) {
  if(s_isPrimed) {
    logThrowGL("[FrameBuffer] Cannot prime default framebuffer while another "
               "FrameBuffer is primed!");
  }

  // bind 0 to context to activate default framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // check framebuffer status and GL errors
  auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(status != GL_FRAMEBUFFER_COMPLETE) {
    // log error message
    logError("[FrameBuffer] Incomplete default framebuffer status<", status, 
             "> while priming! -->");
    
    // print additional information about the error
    switch(status) {
      case GL_FRAMEBUFFER_UNDEFINED:
        logError("[FrameBuffer] The default framebuffer does not exist...");
        break;
      case 0:
        logError("[FrameBuffer] An internal error occured...");
        break;
      default:
        logError("[FrameBuffer] Unknown Error... ");
    }

    // throw exception
    throw GLException(
      "[FrameBuffer] Incomplete default framebuffer status while priming!");
  }
  checkGLError("[FrameBuffer] Error<", GLERR, 
               "> while priming default framebuffer!");

  // create HotFB and call func
  HotFrameBuffer hot(fb);
  func(hot);

  // check GL errors
  checkGLError("[FrameBuffer] Error<", GLERR, "> after priming!");
}

void DefaultFrameBuffer::attachColor(int index, const Tex2D& tex) {
  // warn the user that this operation does not make sense
  logWarning(
    "[FrameBuffer] You can not attach an image to the default framebuffer!");
}

int DefaultFrameBuffer::countAttachments() {
  return 4;
}

} // namespace internal
} // namespace lumina