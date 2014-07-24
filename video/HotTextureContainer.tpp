namespace lumina {

template <TexType... Ts>
HotTextureContainer::HotTextureContainer(const HotTexture<Ts>&... texs)
  : m_count(sizeof...(Ts)) {}

inline HotTextureContainer::HotTextureContainer(int count) :m_count(count) {}


inline int HotTextureContainer::count() const {
  return m_count;
}

}