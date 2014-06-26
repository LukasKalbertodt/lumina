#pragma once

#include "../util/half.hpp"

#include <GL/glew.h>
#include <cstdint>

namespace lumina {

enum class TexFormat {
  R8,
  RGB8,
  RGBA8,

  R16F,
  RGB16F,
  RGBA16F,

  R32F,
  RGB32F,
  RGBA32F,

  D16,
  D32,
  D24S8
};


template <TexFormat> struct TexFormatTrait;


#define X(                                                                     \
  format_, size_, components_, type_, glFormat_, glType_, glInternalFormat_)   \
  template <> struct TexFormatTrait<TexFormat::format_> {                      \
    static constexpr int size = size_;                                         \
    static constexpr int components = components_;                             \
    using type = type_;                                                        \
    static constexpr GLenum glFormat = glFormat_;                              \
    static constexpr GLenum glType = glType_;                                  \
    static constexpr GLint glInternalFormat = glInternalFormat_;               \
  };


X(R8, 1, 1, uint8_t, GL_RED, GL_UNSIGNED_BYTE, GL_R8)
X(RGB8, 3, 3, uint8_t, GL_RGB, GL_UNSIGNED_BYTE, GL_RGB8)
X(RGBA8, 4, 4, uint8_t, GL_RGBA, GL_UNSIGNED_BYTE, GL_RGBA8)
X(R16F, 2, 1, half, GL_RED, GL_HALF_FLOAT, GL_R16F)
X(RGB16F, 6, 3, half, GL_RGB, GL_HALF_FLOAT, GL_RGB16F)
X(RGBA16F, 8, 4, half, GL_RGBA, GL_HALF_FLOAT, GL_RGBA16F)
X(R32F, 4, 1, float, GL_RED, GL_FLOAT, GL_R32F)
X(RGB32F, 12, 3, float, GL_RGB, GL_FLOAT, GL_RGB32F)
X(RGBA32F, 16, 4, float, GL_RGBA, GL_FLOAT, GL_RGBA32F)
X(D16, 2, 1, void, GL_DEPTH_COMPONENT, 0, GL_DEPTH_COMPONENT16)  // TODO: type
X(D32, 4, 1, void, GL_DEPTH_COMPONENT, 0, GL_DEPTH_COMPONENT32)
X(D24S8, 4, 2, void, GL_DEPTH_STENCIL, 0, GL_DEPTH24_STENCIL8)

#undef X


#define X(format_, prop_)\
  case TexFormat::format_: return TexFormatTrait<TexFormat::format_>::prop_;

#define Y(prop_)\
  X(R8, prop_)\
  X(RGB8, prop_)\
  X(RGBA8, prop_)\
  X(R16F, prop_)\
  X(RGB16F, prop_)\
  X(RGBA16F, prop_)\
  X(R32F, prop_)\
  X(RGB32F, prop_)\
  X(RGBA32F, prop_)\
  X(D16, prop_)\
  X(D32, prop_)\
  X(D24S8, prop_)

inline GLenum texFormatToGLFormat(TexFormat format) {
  switch(format) {
    Y(glFormat);
  }
}

inline GLenum texFormatToGLType(TexFormat format) {
  switch(format) {
    Y(glType);
  }
}

inline GLint texFormatToGLInternalFormat(TexFormat format) {
  switch(format) {
    Y(glInternalFormat);
  }
}

#undef Y
#undef X


} // namespace lumina