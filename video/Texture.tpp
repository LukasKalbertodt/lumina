namespace lumina {

template <TexType TT>
Texture<TT>::Texture()
  : m_handle(0) {
}

template <TexType TT>
Texture<TT>::~Texture() {
  // glDeleteTextures ignores 0
  glDeleteTextures(1, &m_handle);
}

template <> inline GLenum Texture<TexType::Tex2D>::glType() const {
  return GL_TEXTURE_2D;
}
template <> inline GLenum Texture<TexType::Tex3D>::glType() const {
  return GL_TEXTURE_3D;
}
template <> inline GLenum Texture<TexType::Cube>::glType() const {
  return GL_TEXTURE_CUBE_MAP;
}

template <TexType TT> 
void Texture<TT>::bindTexture(int texUnit) {
  if(config::debugTexturePrimeChecks) {
    if(TextureUnits::isPrimed(texUnit)) {
      logThrowGL("[Texture] Try to bind a texture to unit <", texUnit, 
                 "> but it's already in use!");
    }
  }

  logDebug("[Texture] Binding handle <", m_handle, "> to unit <", texUnit, ">");
  glActiveTexture(GL_TEXTURE0 + texUnit);
  glBindTexture(glType(), m_handle);
  TextureUnits::setPrimed(texUnit);
}

template <TexType TT> 
void Texture<TT>::unbind(int texUnit) {
  if(config::debugTexturePrimeChecks) {
    if(!TextureUnits::isPrimed(texUnit)) {
      logThrowGL("[Texture] Try to unbind a texture from unit <", texUnit, 
                 "> but it's NOT in use!");
    }
  }

  logDebug("[Texture] Unbinding from unit <", texUnit, "> (my handle: <",
           m_handle, ">)");
  glActiveTexture(GL_TEXTURE0 + texUnit);
  glBindTexture(glType(), 0);
  TextureUnits::unsetPrimed(texUnit);
}

}