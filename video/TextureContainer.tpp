namespace lumina {

template <TexType... Ts>
TextureContainer::TextureContainer(const HotTexture<Ts>&... texs)
  : m_count(sizeof...(Ts)) {}


inline int TextureContainer::count() const {
  return m_count;
}

}