#include "Texture.hpp"
#include "GLException.hpp"
#include "GLTools.hpp"
#include "HotTexture.hpp"


namespace lumina {


template <TexType TT>
void Texture<TT>::create(Vec2i dimension, TexFormat format, void *data) {
  // check if texture was already created
  if(m_handle != 0) {
    logError("[Texture] You can create a texture only once!");
    throw LogicEx("[Texture] You can create a texture only once!");
  }

  // check if another texture is currently primed
  if(TextureUnits::isPrimed(getMaxTexUnits() - 1)) {
    logAndThrow<LogicEx>("[Texture] Cannot execute 'create': Last texture "
                         "unit has to be unused!");
  }

  // check arguments
  if(dimension.x <= 0 || dimension.y <= 0) {
    logError("[Texture] Invalid argument: dimension<",
             dimension, "> is negative!");
    throw InvalidArgEx("[Texture] Invalid argument: dimension is negative");
  }
  // show warnings when strange resolutions are used
  if((dimension.x % 2) != 0 || (dimension.y % 2) != 0) {
    logWarning("[Texture] dimension<", dimension, "> is not MOD 2!");
  }

  // save properties
  m_format = format;
  m_dimension = dimension;

  // create texture and storage for it
  glGenTextures(1, &m_handle);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  bind(getMaxTexUnits() - 1);
  createStorage(dimension,
                texFormatToGLInternalFormat(format),
                texFormatToGLFormat(format),
                texFormatToGLType(format),
                data);

  // apply texture parameter (write strange shit into params to force update)
  applyParams(true);

  // unbind texture: don't leak state
  unbind(getMaxTexUnits() - 1);
  
  checkGLError("[Texture] Error<", GLERR, "> while creating texture!");
}


template <>
void Texture<TexType::Tex2D>::createStorage(Vec2i dim,
                                            GLint internalFormat,
                                            GLenum format,
                                            GLenum type,
                                            void* data) {
  glTexImage2D(
    GL_TEXTURE_2D, 0, internalFormat, dim.x, dim.y, 0, format, type, data);
}

template <>
void Texture<TexType::Tex3D>::createStorage(Vec2i dim,
                                            GLint internalFormat,
                                            GLenum format,
                                            GLenum type,
                                            void* data) {
  // TODO
}

template <>
void Texture<TexType::Cube>::createStorage(Vec2i dim,
                                            GLint internalFormat,
                                            GLenum format,
                                            GLenum type,
                                            void* data) {
  // TODO
}

template <TexType TT>
void Texture<TT>::applyFilterMode() {
  // check for mistakes in parameters 
  if((params.filterMode == TexFilterMode::Trilinear
      || params.filterMode == TexFilterMode::Bilinear)
     && params.useMipMaps == false) {
    logWarning(
      "[Texture] Filtermode was set to bi/trilinear but mipmaps are disabled!");
  }

  // apply filter mode
  switch(params.filterMode) {
    case TexFilterMode::Nearest:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      break;
    case TexFilterMode::Linear:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      break;
    case TexFilterMode::Bilinear:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_MIN_FILTER,
                      GL_LINEAR_MIPMAP_NEAREST);
      break;
    case TexFilterMode::Trilinear:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_MIN_FILTER,
                      GL_LINEAR_MIPMAP_LINEAR);
      break;
  }
}

template <TexType TT>
void Texture<TT>::applyWrapMode() {
  // apply wrap mode
  GLint wrapMode;
  switch(params.wrapMode) {
    case TexWrapMode::Clamp:
      wrapMode = GL_CLAMP_TO_EDGE;
      break;
    case TexWrapMode::Repeat:
      wrapMode = GL_REPEAT;
      break;
    case TexWrapMode::MirrorRepeat:
      wrapMode = GL_MIRRORED_REPEAT;
      break;
  }
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
}

template <TexType TT>
void Texture<TT>::applyMipMaps() {
  if(params.useMipMaps) {
    // OpenGL allocates texture memory for mipmaps and generates them
    glGenerateMipmap(glType());

    // check if any error occured
    checkGLError("[Texture] Error<", GLERR, "> while generating mip maps!");
  }
  else {
    // TODO: Delete mip maps (#36)
  }
}


template <TexType TT>
void Texture<TT>::applyParams(bool force) {
  // check if mip map settings have changed
  if(force || m_activeParams.useMipMaps != params.useMipMaps) {
    applyMipMaps();
    m_activeParams.useMipMaps = params.useMipMaps;
    logDebug("[Texture] MipMaps for texture <", m_handle, 
             "> have been updated!");
  }

  // check if texture filter mode has changed
  if(force || m_activeParams.filterMode != params.filterMode) {
    applyFilterMode();
    m_activeParams.filterMode = params.filterMode;
    logDebug("[Texture] Filter mode for texture <", m_handle, "> was updated!");
  }

  // check if texture wrap mode has changed
  if(force || m_activeParams.wrapMode != params.wrapMode) {
    applyWrapMode();
    m_activeParams.wrapMode = params.wrapMode;
    logDebug("[Texture] Wrap mode for texture <", m_handle, "> was updated!");
  }

  // TODO: apply anisotropic filtering (#37)
}

template<TexType TT>
void Texture<TT>::prePrime(int texUnit) {
  // check if this texture unit is free
  if(config::debugTexturePrimeChecks) {
    if(TextureUnits::isPrimed(texUnit)) {
      logThrowGL("[Texture] Cannot prime: Another Texture is already primed "
                 "on this texture unit <", texUnit, ">!");
    }
  }

  // bind the texture to the given texture unit
  bind(texUnit);

  // update parameters
  applyParams();

  // check if any OpenGL error occured
  checkGLError("[Texture] OpenGL error<", GLERR, "> occured while prePrime!");
}

template<TexType TT>
void Texture<TT>::postPrime(int texUnit) {
  // unbind texture from texture unit
  unbind(texUnit);

  // check if any OpenGL error occured
  checkGLError("[Texture] OpenGL error<", GLERR, "> occured while postPrime!");
}


template <TexType TT>
void Texture<TT>::prime(int texUnit,
                        std::function<void(HotTexture<TT>&)> func) {
  // prepare and bind the texture
  prePrime(texUnit);
  
  // create HotTexture and call function
  HotTexture<TT> hot(*this, texUnit);
  func(hot);

  // cleanup
  postPrime(texUnit);
}


// explicit instantiation
template class Texture<TexType::Tex2D>;
template class Texture<TexType::Tex3D>;
template class Texture<TexType::Cube>;

}