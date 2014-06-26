#pragma once

#include "VertexSlot.hpp"
#include "VertexLayout.hpp"

namespace lumina {
namespace internal {

template <typename... Cs>
class VertexSet {
public:

  // subscript operator
  VertexSlotAssign<Cs...> operator[](int index) {
    // Test if index is valid (not even asan detects overflow: the memory 
    // after this block is somehow allocated by OpenGL anyways)
    if(index >= m_slotCount) {
      throw GLException("[VertexSet] Index out of bounds!");
    }

    // calculate offset and return another helper object
    auto* buf = static_cast<char*>(m_buffer)
                + index * internal::LayoutTypes<Cs...>::stride;
    return VertexSlotAssign<Cs...>(buf);
  }

  int size() { return m_slotCount; }

  void* buf() const { return m_buffer; }

private:
  // internal data
  void* m_buffer;
  int m_slotCount;

  VertexSet(int vertexCount)
    : m_buffer(nullptr),
      m_slotCount((vertexCount * 4) / internal::LayoutTypes<Cs...>::stride) {}

  // declare friends
  friend ::lumina::HotMesh<Cs...>;
};

}
}