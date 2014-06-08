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

template <TexType TT>
void Texture<TT>::create(Vec2i dimension, TexFormat format, void *data) {


  glGenTextures(1, &m_handle);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  bindTexture();
  createStorage(dimension,
                texFormatToGLInternalFormat(format),
                texFormatToGLFormat(format),
                texFormatToGLType(format),
                data);

  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[Texture] Error<",
             translateGLError(err),
             " while creating texture!");
    throw GLException("[Texture] Error while creating texture");
  }
}


template <> GLenum Texture<TexType::Tex2D>::glType() const {
  return GL_TEXTURE_2D;
}

template <> void Texture<TexType::Tex2D>::bindTexture() {
  glBindTexture(GL_TEXTURE_2D, m_handle);
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

}