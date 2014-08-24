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
  // std::cout << Index << ", " << Stride << ", " << Offset << ", " << Size
  //           << std::endl;
  static_assert(Size >= 4, "Incompatible type for vertex layout (to small!)");
  static_assert(Size % 4 == 0,
                "Incompatible type for vertex layout (size not "
                "divisible by 4!)");
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
  static_assert(Size % 4 == 0,
                "Incompatible type for vertex layout (size not "
                "divisible by 4!)");
  // std::cout << Index << ", " << Stride << ", " << Offset << ", " << Size
  //           << std::endl;
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
struct VertexLayout {
  static constexpr int size = VertexLayout<Ts...>::size + sizeof(T);
  static constexpr int count = VertexLayout<Ts...>::count + 1;
};
template <typename T>
struct VertexLayout<T> {
  static constexpr int size = sizeof(T);
  static constexpr int count = 1;
};



}

} // namespace lumina