#pragma once

#include "GLException.hpp"
#include "Mesh.fpp"
#include "../config/BaseProxy.hpp"
#include "IndexSlot.hpp"


namespace lumina {
namespace internal {

class IndexSet : public config::CommonBase {
public:
  IndexSet(int indexCount) : m_buffer(nullptr), m_indexCount(indexCount) {}

  IndexSlot operator[](int index) {
    if(index >= m_indexCount) {
      logError("[IndexSet] Index <", index, "> out of bounds!");
      throw GLException("[IndexSet] Index out of bounds");
    }
    return IndexSlot(*(m_buffer + index));
  }

private:
  unsigned int* m_buffer;
  int m_indexCount;

  template <typename...> friend class ::lumina::HotMesh;
};

}
}