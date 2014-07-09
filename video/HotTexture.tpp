namespace lumina {

template <TexType TT>
HotTexture<TT>::HotTexture(Texture<TT>& ref, int texUnit)
  : param(ref.m_params), m_tex(ref), m_texUnit(texUnit), m_genMipMaps(false) {
  ref.bindTexture(texUnit);
}

template <TexType TT>
HotTexture<TT>::~HotTexture() {
  m_tex.unbind(m_texUnit);
}

}