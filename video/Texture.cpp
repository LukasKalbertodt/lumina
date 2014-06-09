#include "Texture.hpp"
#include "GLException.hpp"
#include "GLTools.hpp"


namespace lumina {

template <TexType TT>
bool Texture<TT>::s_isPrimed = false;

template <TexType TT>
void Texture<TT>::create(Vec2i dimension, TexFormat format, void *data) {
  // check if texture was already created
  if(m_handle != 0) {
    logError("[Texture] You can create a texture only once!");
    throw LogicEx("[Texture] You can create a texture only once!");
  }

  // check if another texture is currently primed
  if(s_isPrimed) {
    logError(
      "[Texture] Cannot execute 'create' while another texture is primed!");
    throw LogicEx(
      "[Texture] Cannot execute 'create' while another texture is primed!");
  }

  // check arguments
  if(dimension.x <= 0 || dimension.y <= 0) {
    logError("[Texture] Invalid argument: dimension<",
             dimension,
             "> is negative!");
    throw InvalidArgEx("[Texture] Invalid argument: dimension is negative");
  }
  // show warnings when strange resolutions are used
  if((dimension.x % 2) != 0 || (dimension.y % 2) != 0) {
    logWarning("[Texture] dimension<", dimension, "> is not MOD 2!");
  }

  // create texture and storage for it
  glGenTextures(1, &m_handle);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  bindTexture();
  createStorage(dimension,
                texFormatToGLInternalFormat(format),
                texFormatToGLFormat(format),
                texFormatToGLType(format),
                data);

  // apply texture parameter
  applyParams();

  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[Texture] Error<",
             translateGLError(err),
             " while creating texture!");
    throw GLException("[Texture] Error while creating texture");
  }
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
void Texture<TT>::applyParams() {
  // apply wrap mode
  GLint wrapMode;
  switch(m_params.wrapMode) {
    case TexWrapMode::Clamp:
      wrapMode = GL_CLAMP_TO_EDGE;
      break;
    case TexWrapMode::Repeat:
      wrapMode = GL_REPEAT;
      break;
    case TexWrapMode::MirrorRepeat:
      wrapMode = GL_MIRRORED_REPEAT;
      break;
    default:
      logError("[Texture] Invalid wrapMode<",
               static_cast<int>(m_params.wrapMode),
               ">!");
      throw CriticalEx("[Texture] Invalid wrapMode");
  }
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);


  // apply filter mode
  switch(m_params.filterMode) {
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

  // TODO: apply anisotropic filtering
}

// explicit instantiation
template class Texture<TexType::Tex2D>;
template class Texture<TexType::Tex3D>;
template class Texture<TexType::Cube>;

}