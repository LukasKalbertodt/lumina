#pragma once

#include "GLObject.hpp"
#include "HotFrameBuffer.fpp"
#include "FBAttachmentPoint.hpp"

#include <GL/glew.h>
#include <functional>
#include <vector>

namespace lumina {

class FrameBuffer : public GLObject {
public:
  FrameBuffer();
  FrameBuffer(FrameBuffer&&);

  ~FrameBuffer();

  void create();
  void prime(std::function<void(HotFrameBuffer&)> func);

  internal::FBAttachmentPoint operator[](int index);


private:
  GLuint m_handle;
  std::vector<GLuint> m_attachments;
  bool m_needsUpdate;

  static bool s_isPrimed;

  void updateState();
  void bind();
  void unbind();

  friend HotFrameBuffer;
};

}

#include "FrameBuffer.tpp"