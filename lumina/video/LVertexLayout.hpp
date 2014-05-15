#pragma once

#include <GL/glew.h>

#include <cstdint>
#include <type_traits>
#include <iostream>

namespace lumina {

namespace internal {

template <int Index,
          int Stride,
          int Offset,
          int Size,
          int... Tail>
typename std::enable_if<sizeof...(Tail) == 0>::type applyLayoutImpl() {
  static_assert(Size >= 4, "Incompatible type for vertex layout (to small!)");
  glVertexAttribPointer(Index,
                        Size/4,
                        GL_FLOAT,
                        GL_FALSE,
                        Stride,
                        reinterpret_cast<void*>(Offset));
  glEnableVertexAttribArray(Index);
}

template <int Index,
          int Stride,
          int Offset,
          int Size,
          int... Tail>
typename std::enable_if<sizeof...(Tail) != 0>::type applyLayoutImpl() {
  static_assert(Size >= 4, "Incompatible type for vertex layout (to small!)");
  glVertexAttribPointer(Index,
                        Size/4,
                        GL_FLOAT,
                        GL_FALSE,
                        Stride,
                        reinterpret_cast<void*>(Offset));
  glEnableVertexAttribArray(Index);
  applyLayoutImpl<Index + 1, Stride, Offset + Size, Tail...>();
}

template <typename T, typename... Ts>
struct LayoutTypes {
  static constexpr int stride = LayoutTypes<Ts...>::stride + sizeof(T);
};
template <typename T>
struct LayoutTypes<T> {
  static constexpr int stride = sizeof(T);
};

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

  template<typename... Ts>
  static void applyVertexLayout() {
    internal::applyLayoutImpl<0,
                              internal::LayoutTypes<Ts...>::stride,
                              0,
                              sizeof(Ts)...>();
  }

  
  // friend declarations
  template <typename...>
  friend LVertexLayout createVertexLayout();
  friend class LMesh;
};


template <typename... Ts>
LVertexLayout createVertexLayout() {
  return LVertexLayout(&LVertexLayout::applyVertexLayout<Ts...>);
}

} // namespace lumina