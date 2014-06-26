#include "HotTexture.hpp"

#include "GLTools.hpp"
#include "GLException.hpp"

namespace lumina {

template <TexType TT>
void HotTexture<TT>::fill(void* data) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  fillSubData(texFormatToGLFormat(m_tex.m_format),
              texFormatToGLType(m_tex.m_format),
              data);
  m_genMipMaps = true;

  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[HotTexture] Error<", translateGLError(err),
             "> while filling data!");
    throw GLException("[HotTexture] Error while filling data");
  }
}

template <>
void HotTexture<TexType::Tex2D>::fillSubData(GLenum format,
                                             GLenum type,
                                             void* data) {
  glTexSubImage2D(GL_TEXTURE_2D,
                  0, 0, 0,
                  m_tex.m_dimension.x,
                  m_tex.m_dimension.y,
                  format, type, data);
}

template <>
void HotTexture<TexType::Tex3D>::fillSubData(GLenum format,
                                             GLenum type,
                                             void* data) {
  // TODO
}

template <>
void HotTexture<TexType::Cube>::fillSubData(GLenum format,
                                             GLenum type,
                                             void* data) {
  // TODO 
}




template class HotTexture<TexType::Tex2D>;
template class HotTexture<TexType::Tex3D>;
template class HotTexture<TexType::Cube>;

}