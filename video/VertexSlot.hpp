#pragma once

#include "VertexSlot.fpp"
#include "GLException.hpp"
#include "../service/StaticLogger.hpp"

#include <initializer_list>
#include <cstring>

namespace lumina {

template <typename T, typename... Ts>
class VertexSlot {
public:
  VertexSlot(void* buffer);

  void set(T head, Ts... tail);

  template <typename...> friend class VertexSet;
  template <typename, typename...> friend class VertexSlot;

private:
  void* m_buffer;
};

template <typename T>
class VertexSlot<T> {
public:
  VertexSlot(void* buffer);

  void operator=(T data);

  void set(T head);

  template <typename...> friend class VertexSet;
  template <typename, typename...> friend class VertexSlot;

private:
  void* m_buffer;
};


} // namespace lumina

#include "VertexSlot.tpp"