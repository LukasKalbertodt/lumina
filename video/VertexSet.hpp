#pragma once

#include "GLException.hpp"
#include "VertexSlot.hpp"
#include "VertexLayout.hpp"
#include "../service/StaticLogger.hpp"

namespace lumina {

template <typename... Cs>
class VertexSet {
public:
  VertexSet(int vertexCount, void* buffer);

  /// Subscript operator to access a single VertexSlot
  VertexSlot<Cs...> operator[](int index);

  /// Number of vertices in this set
  int size() const;

  // Internal pointer to the vertex buffer  
  void* buf() const;


private:
  void* m_buffer;
  int m_slotCount;
};

// template <>
// class VertexSet<> {
// public:
//   // subscript operator
//   VertexFloatSlot operator[](int index) {
//     // Test if index is valid (not even asan detects overflow: the memory 
//     // after this block is somehow allocated by OpenGL anyways)
//     if(index >= m_slotCount) {
//       slogError("[VertexSet] Index <", index, "> out of bounds <", 
//                 m_slotCount, ">!");
//       throw GLException("[VertexSet] Index out of bounds!");
//     }

//     // calculate offset and return another helper object
//     auto* buf = static_cast<char*>(m_buffer)
//                 + index * m_slotSize * sizeof(float);
//     return VertexFloatSlot(buf, m_slotSize);
//   }

//   int size() { return m_slotCount; }

//   void* buf() const { return m_buffer; }

// private:
//   // internal data
//   void* m_buffer;
//   int m_slotCount;
//   int m_slotSize;

//   VertexSet(int vertexCount, int slotSize)
//     : m_buffer(nullptr),
//       m_slotCount(vertexCount),
//       m_slotSize(slotSize) {}

//   // declare friends
//   friend ::lumina::HotVertexSeq<>;
// };


} // namespace lumina

#include "VertexSet.tpp"