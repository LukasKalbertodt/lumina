#pragma once

#include "GLObject.hpp"
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

class TextureInterface : public GLObject {
public:
  virtual ~TextureInterface() = default;

  virtual void prePrime(int texUnit) = 0;
  virtual void postPrime(int texUnit) = 0;
};

template <TexType TT>
class Texture : public TextureInterface {
public:
  TexParam params;

  Texture();
  ~Texture();

  void create(Vec2i dimension, TexFormat format, void *data = nullptr);
  void prime(int texUnit, std::function<void(HotTexture<TT>&)> func);

  GLuint nativeHandle() const;
  TexFormat getFormat() const;


private:
  GLuint m_handle;
  Vec2i m_dimension;
  TexParam m_activeParams;
  TexFormat m_format;

  void prePrime(int texUnit) final;
  void postPrime(int texUnit) final;

  void bind(int texUnit);
  void unbind(int texUnit);

  void applyParams(bool force = false);
  void applyFilterMode();
  void applyWrapMode();
  void applyMipMaps();

  GLenum glType() const;
  void createStorage(Vec2i dim,
                     GLint internalFormat,
                     GLenum format,
                     GLenum type,
                     void* data);

  friend HotTexture<TT>;
};

} // namespace lumina

#include "Texture.tpp"