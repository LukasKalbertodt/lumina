#pragma once
/**
 * \file Texture.hpp
 * Defines the Texture class that represents a OpenGL texture.
 * 
 * This file is part of the Lumina Graphics Library
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 */

#include "GLObject.hpp"
#include "HotTexture.fpp"
#include "TexFormat.hpp"
#include "TexParam.hpp"
#include "Texture.fpp"
#include "TextureUnits.hpp"
#include "TexType.hpp"
#include "../config/BaseProxy.hpp"
#include "../util/Vector.hpp"

#include <GL/glew.h>
#include <functional>
#include <vector>

namespace lumina {

/**
 * \brief Interface for all texture types (2D, 3D, Cube). 
 * It's currently just used in the TextureCont. 
 */
class TextureInterface : public GLObject {
public:
  virtual ~TextureInterface() = default;

  virtual void prePrime(int texUnit) = 0;
  virtual void postPrime(int texUnit) = 0;
};


/**
 * \brief Represents an OpenGL texture.
 * There are different kinds of textures: 2D, 3D and Cube. 2D is the most
 * commonly used one. Currently only 2D works!
 * 
 * \tparam TT Type of the Texture (2D, 3D or Cube)
 */
template <TexType TT>
class Texture : public TextureInterface {
public:
  TexParam params;

  Texture();
  ~Texture();

  /**
   * \brief Creates internal storage for the texture.
   * All internal data structures are created and optional data is filled
   * into the texture memory. 
   * 
   * \param dimension Size of the texture
   * \param format Format of the texture
   * \param data A pointer to valid texture data
   */
  void create(Vec2i dimension, TexFormat format, void *data = nullptr);
  void prime(int texUnit, std::function<void(HotTexture<TT>&)> func);

  GLuint nativeHandle() const;
  TexFormat getFormat() const;
  Vec2i getDimension() const;

  explicit operator bool() const;


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