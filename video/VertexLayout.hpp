#pragma once

#include "../util/VectorCore.hpp"

#include <GL/glew.h>

#include <cstdint>
#include <type_traits>
#include <iostream>

namespace lumina {

namespace internal {

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


template <typename T> struct VertexAttributeType;

#define X_VAT(type_, gltype_)                                                  \
  template <> struct VertexAttributeType<type_> {                              \
    static constexpr bool valid = true;                                        \
    static constexpr GLenum type = gltype_;                                    \
  };

X_VAT(float, GL_FLOAT)
X_VAT(uint32_t, GL_UNSIGNED_INT)
X_VAT(int32_t, GL_INT)
X_VAT(uint16_t, GL_UNSIGNED_SHORT)
X_VAT(int16_t, GL_SHORT)
X_VAT(uint8_t, GL_UNSIGNED_BYTE)
X_VAT(int8_t, GL_BYTE)

#undef X_VAT

template <typename T>
struct VertexAttribute {
  static constexpr bool valid = VertexAttributeType<T>::valid;
  static constexpr GLenum type = VertexAttributeType<T>::type;
  static constexpr int components = 1;  
};

template <typename T, std::size_t N>
struct VertexAttribute<Vector<T, N>> {
  static constexpr bool valid = VertexAttributeType<T>::valid;
  static constexpr int components = N;
  static constexpr GLenum type = VertexAttributeType<T>::type;
};




template <typename T, int Index, int Offset, int Stride>
typename std::enable_if<true>::type applyLayoutAttrib() {
  static_assert(VertexAttribute<T>::valid, "");

  glVertexAttribPointer(Index,
                        VertexAttribute<T>::components,
                        VertexAttribute<T>::type,
                        GL_FALSE,
                        Stride,
                        reinterpret_cast<void*>(Offset));
  glEnableVertexAttribArray(Index);
}

template <int Index, int Stride, int Offset, typename T, typename... Tail>
typename std::enable_if<sizeof...(Tail) == 0>::type applyVertexLayout() {
  applyLayoutAttrib<T, Index, Offset, Stride>();
  applyVertexLayout<Index + 1, Stride, Offset + sizeof(T), Tail...>();
}

template <int Index, int Stride, int Offset, typename T, typename... Tail>
typename std::enable_if<sizeof...(Tail) != 0>::type applyVertexLayout() {
  applyLayoutAttrib<T, Index, Offset, Stride>();
}



} // namespace internal

} // namespace lumina