#pragma once

#include "HotTexture.fpp"
#include "TexFormat.hpp"
#include "TextureUnits.hpp"
#include "TexParam.hpp"
#include "Texture.fpp"
#include "TexType.hpp"
#include "../config/BaseProxy.hpp"
#include "../util/Vector.hpp"

#include <GL/glew.h>
#include <functional>
#include <vector>

namespace lumina {

template <TexType TT>
class Texture : public config::CommonBase {
public:
  Texture();
  ~Texture();

  void create(Vec2i dimension, TexFormat format, void *data = nullptr);
  void prime(/*int texUnit,*/ std::function<void(HotTexture<TT>&)> func);


  void bindTexture(/*int texUnit*/);
  void unbind();

private:
  GLuint m_handle;
  Vec2i m_dimension;
  TexParam m_params;
  TexFormat m_format;

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