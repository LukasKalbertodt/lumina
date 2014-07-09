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
  logDebug("[Texture] Binding handle <", m_handle, "> to unit <", texUnit, ">");
  glActiveTexture(GL_TEXTURE0 + texUnit);
  glBindTexture(glType(), m_handle);
}

template <TexType TT> 
void Texture<TT>::unbind(int texUnit) {
  logDebug("[Texture] Unbinding from unit <", texUnit, "> (my handle: <",
           m_handle, ">)");
  glActiveTexture(GL_TEXTURE0 + texUnit);
  glBindTexture(glType(), 0);
}

}