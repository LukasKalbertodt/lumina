#pragma once

#include "GLObject.hpp"
#include "../util/VectorCore.hpp"

#include <GL/glew.h>

namespace lumina {

enum class RenderBufferType {
  Depth16, Depth32, Depth24Stencil8
};


class RenderBuffer : public GLObject {
public:
  RenderBuffer();

  void create(Vec2i size, RenderBufferType type);

  RenderBufferType getType() const;
  GLuint nativeHandle() const;


private:
  RenderBufferType m_type;
  GLuint m_handle;
  Vec2i m_size;

  static bool s_primed;
};

} // namespace lumina

#include "RenderBuffer.tpp"