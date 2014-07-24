namespace lumina {

template <TexType TT>
HotTexture<TT>::HotTexture(Texture<TT>& ref, int texUnit)
  : m_tex(ref), m_texUnit(texUnit) {
  // Texture::prime checked that texUnit is free
  // ref.bind(texUnit);
}

template <TexType TT>
HotTexture<TT>::~HotTexture() {
  // m_tex.unbind(m_texUnit);
}

}