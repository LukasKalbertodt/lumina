#pragma once

#include <GL/glew.h>

namespace lumina {

class FrameBuffer {
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