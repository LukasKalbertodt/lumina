#pragma once

#include "TexFormat.hpp"
#include "TexType.hpp"
#include "../util/Vector.hpp"
#include "../config/BaseProxy.hpp"

#include <GL/glew.h>

namespace lumina {

template <TexType TT>
class Texture : public config::CommonBase {
public:
  Texture();
  ~Texture();

  void create(Vec2i dimension, TexFormat format, void *data = nullptr);

private:
  GLuint m_handle;
  Vec2i m_dimension;

  GLenum glType() const;
  void createStorage(Vec2i dim,
                     GLint internalFormat,
                     GLenum format,
                     GLenum type,
                     void* data);
  void bindTexture();
};


} // namespace lumina

#include "Texture.tpp"