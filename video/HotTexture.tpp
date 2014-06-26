namespace lumina {

template <TexType TT>
HotTexture<TT>::HotTexture(Texture<TT>& ref)
  : param(ref.m_params), m_tex(ref), m_genMipMaps(false) {
  ref.bindTexture();
}

template <TexType TT>
HotTexture<TT>::~HotTexture() {
  m_tex.unbind();
}

}