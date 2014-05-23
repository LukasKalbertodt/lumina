#pragma once

#include "GLException.hpp"
#include "Mesh.fpp"
#include "../config/BaseProxy.hpp"


namespace lumina {
namespace internal {

class IndexSet : public config::CommonBase {
public:
  IndexSet(int indexCount) : m_buffer(nullptr), m_indexCount(indexCount) {}

  int& operator[](int index) {
    if(index >= m_indexCount) {
      logError("[IndexSet] Index <", index, "> out of bounds!");
      throw GLException("[IndexSet] Index out of bounds");
    }
    return *(m_buffer + index);
  }

private:
  int* m_buffer;
  int m_indexCount;

  template <typename...> friend class ::lumina::HotMesh;
};

}
}