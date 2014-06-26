#pragma once

#include <GL/glew.h>
#include "GLObject.hpp"

namespace lumina {

class FrameBuffer : public GLObject {
public:
  FrameBuffer();
  FrameBuffer(FrameBuffer&&);

  ~FrameBuffer();

  void create();
  void prime();


private:
  GLuint m_handle;

};

}

#include "FrameBuffer.tpp"