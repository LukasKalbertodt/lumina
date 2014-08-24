#pragma once

#include "GLIndex.hpp"
#include "../config/BaseProxy.hpp"
#include <limits>

namespace lumina {

class IndexSlot : public config::CommonBase {
public:
  IndexSlot(unsigned int& data);

  IndexSlot& operator=(unsigned int v);
  IndexSlot& operator=(const IndexSlot& copy);
  IndexSlot& operator=(GLIndex);

private:
  unsigned int& m_data;
};

} // namespace lumina

#include "IndexSlot.tpp"