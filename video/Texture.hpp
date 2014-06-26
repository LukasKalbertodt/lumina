#pragma once

#include "GLObject.hpp"
#include "HotTexture.fpp"
#include "TexFormat.hpp"
#include "TexParam.hpp"
#include "Texture.fpp"
#include "TexType.hpp"
#include "../config/BaseProxy.hpp"
#include "../util/Vector.hpp"

#include <GL/glew.h>
#include <functional>

namespace lumina {

template <TexType TT>
class Texture : public GLObject {
public:
  Texture();
  ~Texture();

  void create(Vec2i dimension, TexFormat format, void *data = nullptr);
  void prime(std::function<void(HotTexture<TT>&)> func);


  void bindTexture();
  void unbind();

private:
  GLuint m_handle;
  Vec2i m_dimension;
  TexParam m_params;
  TexFormat m_format;

  static bool s_isPrimed;

  GLenum glType() const;
  void createStorage(Vec2i dim,
                     GLint internalFormat,
                     GLenum format,
                     GLenum type,
                     void* data);
  void applyParams();

  friend HotTexture<TT>;
};


} // namespace lumina

#include "Texture.tpp"