#pragma once

#include "TexFormat.hpp"
#include "TexType.hpp"
#include "TexParam.hpp"
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
  void bindTexture();

private:
  GLuint m_handle;
  Vec2i m_dimension;
  TexParam m_params;

  static bool s_isPrimed;

  GLenum glType() const;
  void createStorage(Vec2i dim,
                     GLint internalFormat,
                     GLenum format,
                     GLenum type,
                     void* data);
  void applyParams();
};


} // namespace lumina

#include "Texture.tpp"