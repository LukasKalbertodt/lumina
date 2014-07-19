#pragma once

#include "VertexSlot.fpp"
#include "GLException.hpp"
#include "../service/StaticLogger.hpp"

#include <initializer_list>
#include <cstring>

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

class VertexFloatSlot {
public:
  VertexFloatSlot(void* buf, int size) : m_buffer(buf), m_size(size) {}

  float& operator[](int index) {
    if(index >= m_size) {

    }
    return static_cast<float*>(this->m_buffer)[index];
  }
  void operator=(std::initializer_list<float> data) {
    if(data.size() > m_size) {
      slogError("[VertexSlot] Size of initializer_list <", data.size(),
                "> bigger than size of the slot <", m_size, ">!");
      throw GLException("[VertexSlot] Size of initializer_list bigger than "
                        "size of the slot");
    }
    std::memcpy(this->m_buffer, data.begin(), data.size() * sizeof(float));
  }

  template <typename...> friend class VertexSet;
  template <typename, typename...> friend class VertexSlotAssign;

private:
  void* m_buffer;
  int m_size;
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