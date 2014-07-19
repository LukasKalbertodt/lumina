#pragma once

#include "Texture.hpp"

namespace lumina {
namespace internal {

class FBAttachmentPoint {
public:
  FBAttachmentPoint(GLuint& handle, bool& needsUpdate)
    : m_handle(handle), m_needsUpdate(needsUpdate) {}

  void operator=(Tex2D tex) {
    if(m_handle != tex.nativeHandle()) {
      m_handle = tex.nativeHandle();
      m_needsUpdate = true;
    }
  }

private:
  GLuint& m_handle;
  bool& m_needsUpdate;
};

}
}