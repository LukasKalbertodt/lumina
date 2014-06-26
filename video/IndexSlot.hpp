#pragma once

#include "GLIndex.hpp"
#include <limits>

namespace lumina {
namespace internal {

class IndexSlot : public config::CommonBase {
public:
  IndexSlot(unsigned int& data) : m_data(data) {}

  IndexSlot& operator=(unsigned int v) {
    m_data = v;
    return *this;
  }
  IndexSlot& operator=(IndexSlot& copy) {
    m_data = copy.m_data;
    return *this;
  }
  IndexSlot& operator=(GLIndex) {
    m_data = std::numeric_limits<unsigned int>::max();
    return *this;
  }


private:
  unsigned int& m_data;
};

}
}