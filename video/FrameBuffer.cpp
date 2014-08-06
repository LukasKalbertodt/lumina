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
  int countColor = 0;
  for(int i = 0; i < m_colorAtts.size(); ++i) {
    auto& tex = m_colorAtts[i];
    if(tex.handle != 0) {
      countColor++;
      glFramebufferTexture(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0 + i,
                           tex.handle, 0);
      drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
  }

  if(m_depthAtt != 0) {
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthAtt, 0);
  }
  else if(m_depthStencilAtt != 0) {
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, 
                         m_depthStencilAtt, 0);
  }

  // specify which attachment points to use
  glDrawBuffers(m_colorAtts.size(), drawBuffers.data());

  // check for errors
  checkGLError("[FrameBuffer] Error<", GLERR, "> while updating state!");

  // reset flag and log
  if(config::logDebugEveryFrame) {
    logDebug("[FrameBuffer] Updated framebuffer<", m_handle, "> state with <", 
             countColor, "> color attachments",
             (m_depthAtt != 0) ? " and a custom depth attachment" : "");
  }
  m_needsUpdate = false;
}

void UserFrameBuffer::prime(std::shared_ptr<FrameBufferInterface> fb,
                            std::function<void(HotFrameBuffer&)> func) {
  if(s_isPrimed) {
    logThrowGL(
      "[FrameBuffer] Cannot prime while another FrameBuffer is primed!");
  }
  // set primed flag
  s_isPrimed = true;

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

  // reset primed flag
  s_isPrimed = false;
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
  auto& point = m_colorAtts[index];
  if(point.handle != tex.nativeHandle()) {
    point.handle = tex.nativeHandle();
    point.format = f;
    m_needsUpdate = true;
  }
}

void UserFrameBuffer::attachDepth(const Tex2D& tex) {
  // check texture format
  auto f = tex.getFormat();
  if(f != TexFormat::D16 && f != TexFormat::D32) {
    logAndThrow<InvalidArgEx>("[FrameBuffer] You cannot attach a texture "
                              "without a depth format to a depth attachment "
                              "point!");
  }

  if(m_depthStencilAtt != 0) {
    logAndThrow<LogicEx>("[FrameBuffer] Trying to attach a depth image, but "
                         "a depth-stencil image is already attached!");
  }

  // assign values if the values are distinct
  if(m_depthAtt != tex.nativeHandle()) {
    m_depthAtt = tex.nativeHandle();
    m_needsUpdate = true;
  }
}

void UserFrameBuffer::attachDepthStencil(const Tex2D& tex) {
  // check texture format
  auto f = tex.getFormat();
  if(f != TexFormat::D24S8) {
    logAndThrow<InvalidArgEx>("[FrameBuffer] You cannot attach a texture "
                              "without a depth-stencil format to a " 
                              "depth-stencil attachment point!");
  }

  if(m_depthAtt != 0) {
    logAndThrow<LogicEx>("[FrameBuffer] Trying to attach a depth-stencil image"
                         ", but a depth image is already attached!");
  }

  // assign values if the values are distinct
  if(m_depthStencilAtt != tex.nativeHandle()) {
    m_depthStencilAtt = tex.nativeHandle();
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

void UserFrameBuffer::clearColor(int index, Color32fA color) {
  if(index >= m_colorAtts.size()) {
    logAndThrow<OutOfRangeEx>("[FrameBuffer] Index<", index, "> of attachment "
                              "to clear is higher than the number of "
                              "attachements<", m_colorAtts.size(), ">!");
  }
  // auto& point = m_colorAtts[index];
  // auto f = point.format;
  // if(!(f == TexFormat::R8 || f == TexFormat::RGB8 || f == TexFormat::RGBA8)) {
  //   logAndThrow<InvalidArgEx>("[HotFrameBuffer] You can not clear a "
  //                             "floating point texture with a integer color "
  //                             "format!");
  // }

  GLfloat d[4] = {color.r, color.g, color.b, color.a};
  glClearBufferfv(GL_COLOR, index, d);

  checkGLError("[FrameBuffer] Error while clearing attachment<", index, ">!");
}


void UserFrameBuffer::clearDepth(float val) {
  glClearBufferfv(GL_DEPTH, 0, &val);

  checkGLError("[FrameBuffer] Error while clearing depth attachment!");
}

void UserFrameBuffer::clearDepthStencil(float depth, int stencil) {
  glClearBufferfi(GL_DEPTH_STENCIL, 0, depth, stencil);

  checkGLError("[FrameBuffer] Error while clearing depth-stencil attachment!");
}



void DefaultFrameBuffer::prime(std::shared_ptr<FrameBufferInterface> fb,
                            std::function<void(HotFrameBuffer&)> func) {
  if(s_isPrimed) {
    logThrowGL("[FrameBuffer] Cannot prime default framebuffer while another "
               "FrameBuffer is primed!");
  }
  // set primed flag
  s_isPrimed = true;

  // activate back buffer for drawing
  GLenum drawbuffers = GL_BACK_LEFT;
  glDrawBuffers(1, &drawbuffers);

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

  // reset primed flag
  s_isPrimed = false;
}

void DefaultFrameBuffer::attachColor(int index, const Tex2D& tex) {
  // warn the user that this operation does not make sense
  logWarning(
    "[FrameBuffer] You can not attach an image to the default framebuffer!");
}

void DefaultFrameBuffer::attachDepth(const Tex2D& tex) {
  // warn the user that this operation does not make sense
  logWarning(
    "[FrameBuffer] You can not attach an image to the default framebuffer!");
}

void DefaultFrameBuffer::attachDepthStencil(const Tex2D& tex) {
  // warn the user that this operation does not make sense
  logWarning(
    "[FrameBuffer] You can not attach an image to the default framebuffer!");
}

int DefaultFrameBuffer::countAttachments() {
  return 4;
}


void DefaultFrameBuffer::clearColor(int index, Color32fA color) {
  if(index != 0) {
    // warn the user that index has no effect
    logWarning("[FrameBuffer] Using an index other than 0 does not have any "
               "effect when using the default framebuffer!");
  }

  GLfloat d[4] = {color.r, color.g, color.b, color.a};
  glClearBufferfv(GL_COLOR, 0, d);

  checkGLError("[FrameBuffer] Error while clearing attachment<", index, ">!");
}

void DefaultFrameBuffer::clearDepth(float val) {
  glClearBufferfv(GL_DEPTH, 0, &val);

  checkGLError("[FrameBuffer] Error while clearing depth attachment!");
}

void DefaultFrameBuffer::clearDepthStencil(float depth, int stencil) {
  glClearBufferfi(GL_DEPTH_STENCIL, 0, depth, stencil);

  checkGLError("[FrameBuffer] Error while clearing depth-stencil attachment!");
}

} // namespace internal
} // namespace lumina