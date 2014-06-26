#pragma once

#include <stdexcept>

namespace lumina {

class LuminaException : public std::runtime_error {
  // inherit constructor
  using std::runtime_error::runtime_error;
};


#define X(name_, base_)\
  class name_ : public base_ {\
    using base_::base_;\
  };

X(NotReadyEx, LuminaException)
X(LogicEx, LuminaException)
X(InvalidArgEx, LuminaException)
X(CriticalEx, LuminaException)
X(IOEx, LuminaException)

#undef X

} // namespace lumina