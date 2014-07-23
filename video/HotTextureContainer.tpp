namespace lumina {

template <TexType... Ts>
HotTextureContainer::HotTextureContainer(const HotTexture<Ts>&... texs)
  : m_count(sizeof...(Ts)) {}


inline int HotTextureContainer::count() const {
  return m_count;
}

}