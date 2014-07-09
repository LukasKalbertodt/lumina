#pragma once

#include <GL/glew.h>

namespace lumina {

enum class PrimitiveType {
  Point = GL_POINTS,
  Line = GL_LINES,
  LineStrip = GL_LINE_STRIP, 
  Triangle = GL_TRIANGLES,
  TriangleStrip = GL_TRIANGLE_STRIP,
  TriangleFan = GL_TRIANGLE_FAN
};

inline GLenum translatePrimitiveType(PrimitiveType type) {
  return static_cast<GLenum>(type);
}

}