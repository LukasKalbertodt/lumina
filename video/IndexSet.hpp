#pragma once

#include "IndexSlot.hpp"
#include "GLException.hpp"
#include "GLObject.hpp"
#include "VertexSeq.fpp"
#include "../config/BaseProxy.hpp"


namespace lumina {

class IndexSet : public GLObject {
public:
  IndexSet(int indexCount, unsigned int* buffer); 

  IndexSlot operator[](int index);

private:
  unsigned int* m_buffer;
  int m_indexCount;
};

} // namespace lumina

#include "IndexSet.tpp"