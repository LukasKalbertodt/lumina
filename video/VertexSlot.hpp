#pragma once

#include "VertexSlot.fpp"

namespace lumina {
namespace internal {

class VertexSlot {
protected:
  void* m_buffer;

  VertexSlot(void* buf) : m_buffer(buf) {}
};

template <typename T, typename... Ts>
class VertexSlotAssign : public VertexSlot {
public:
  using VertexSlot::VertexSlot;

  VertexSlotComma<Ts...> operator=(T data) {
    *static_cast<T*>(this->m_buffer) = data;
    return VertexSlotComma<Ts...>(static_cast<T*>(this->m_buffer) + 1);
  }

  void set(T head, Ts... tail) {
    *static_cast<T*>(this->m_buffer) = head;
    VertexSlotAssign<Ts...>(static_cast<T*>(this->m_buffer) + 1).set(tail...);
  }

  template <typename...> friend class VertexSet;
  template <typename, typename...> friend class VertexSlotAssign;
};

template <typename T>
class VertexSlotAssign<T> : public VertexSlot {
public:
  using VertexSlot::VertexSlot;

  void operator=(T data) { *static_cast<T*>(this->m_buffer) = data; }

  void set(T head) { *static_cast<T*>(this->m_buffer) = head; }

  template <typename...> friend class VertexSet;
  template <typename, typename...> friend class VertexSlotAssign;
};


template <typename T, typename... Ts>
class VertexSlotComma : public VertexSlot {
public:
  using VertexSlot::VertexSlot;

  VertexSlotComma<Ts...> operator,(T data) {
    *static_cast<T*>(this->m_buffer) = data;
    return VertexSlotComma<Ts...>(static_cast<T*>(this->m_buffer) + 1);
  }

  template <typename, typename...> friend class VertexSlotAssign;
};

template <typename T>
class VertexSlotComma<T> : public VertexSlot {
public:
  using VertexSlot::VertexSlot;

  void operator,(T data) { *static_cast<T*>(this->m_buffer) = data; }

  template <typename, typename...> friend class VertexSlotAssign;
  template <typename, typename...> friend class VertexSlotComma;
};


}
}