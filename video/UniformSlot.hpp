#pragma once

#include "Program.fpp"
#include "UniformSet.fpp"
#include "../config/BaseProxy.hpp"
#include "../util/VectorCore.hpp"
#include "../util/NonCopyable.hpp"

namespace lumina { 
namespace internal {

struct UniformSlot : public config::CommonBase {
public:

  void operator=(float val);
  template <typename T, std::size_t N>
  void operator=(Vector<T, N> val);

private:
  GLuint index;

  UniformSlot(GLuint index) : index(index) {}

  friend UniformSet;
};

}
}