#pragma once

#include <GL/glew.h>

#include <cstdint>
#include <type_traits>
#include <iostream>

namespace lumina {

enum class LVertexComponent {
  None,
  Pos3D,
  Pos2D,
  Color,
  Normal,
  Tangent,
  TexCoord
};

namespace internal {

template <LVertexComponent C>
struct LVertexCompTraits;

#define X(comp_, size_)                                                        \
  template <> struct LVertexCompTraits<LVertexComponent::comp_> {              \
    static constexpr int size = size_;                                         \
  }

X(Pos3D, 3);
X(Pos2D, 2);
X(Color, 3);
X(Normal, 3);
X(Tangent, 3);
X(TexCoord, 2);

#undef X


template <LVertexComponent Head, LVertexComponent... Tail>
struct LVertexCompHelper {
  static constexpr int stride = LVertexCompHelper<Tail...>::stride
                                + LVertexCompTraits<Head>::size;
};

template <LVertexComponent Head>
struct LVertexCompHelper<Head> {
  static constexpr int stride = LVertexCompTraits<Head>::size;
};


template <int Index,
          int Stride,
          int Offset,
          LVertexComponent Head,
          LVertexComponent... Tail>
typename std::enable_if<sizeof...(Tail) == 0>::type applyLayoutImpl() {
  glVertexAttribPointer(Index,
                        internal::LVertexCompTraits<Head>::size,
                        GL_FLOAT,
                        GL_FALSE,
                        Stride * 4,
                        reinterpret_cast<void*>(Offset * 4));
  glEnableVertexAttribArray(Index);
}

template <int Index,
          int Stride,
          int Offset,
          LVertexComponent Head,
          LVertexComponent... Tail>
typename std::enable_if<sizeof...(Tail) != 0>::type applyLayoutImpl() {
  glVertexAttribPointer(Index,
                        internal::LVertexCompTraits<Head>::size,
                        GL_FLOAT,
                        GL_FALSE,
                        Stride * 4,
                        reinterpret_cast<void*>(Offset * 4));
  glEnableVertexAttribArray(Index);
  applyLayoutImpl<Index + 1,
                  Stride,
                  Offset + internal::LVertexCompTraits<Head>::size,
                  Tail...>();
}

}

class LVertexLayout {
public:
  LVertexLayout() : m_delegate(nullptr) {}


private:
  void (*m_delegate)();

  LVertexLayout(void(*delegate)()) : m_delegate(delegate) {}

  void apply() {
    if(m_delegate) {
      m_delegate();
    }
  }

  template<LVertexComponent... Comp>
  static void applyVertexLayout() {
    internal::applyLayoutImpl<0,
                            internal::LVertexCompHelper<Comp...>::stride,
                            0,
                            Comp...>();
  }

  
  // friend declarations
  template <LVertexComponent...>
  friend LVertexLayout createVertexLayout();
  friend class LRawMesh;
};


template <LVertexComponent... Components>
LVertexLayout createVertexLayout() {
  return LVertexLayout(&LVertexLayout::applyVertexLayout<Components...>);
}

} // namespace lumina