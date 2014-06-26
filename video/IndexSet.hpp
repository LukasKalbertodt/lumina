#pragma once

#include "IndexSlot.hpp"
#include "GLException.hpp"
#include "GLObject.hpp"
#include "Mesh.fpp"
#include "../config/BaseProxy.hpp"


namespace lumina {
namespace internal {

class IndexSet : public GLObject {
public:
  IndexSet(int indexCount) : m_buffer(nullptr), m_indexCount(indexCount) {}

  IndexSlot operator[](int index) {
    if(index >= m_indexCount) {
      logError("[IndexSet] Index <", index, "> out of bounds!");
      throw GLException("[IndexSet] Index out of bounds");
    }
    return std::move(IndexSlot(*(m_buffer + index)));
  }

private:
  unsigned int* m_buffer;
  int m_indexCount;

  template <typename...> friend class ::lumina::HotMesh;
};

}
}