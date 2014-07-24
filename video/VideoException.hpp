#pragma once

#include "../core/LuminaException.hpp"

namespace lumina {

#define MAKE_EX(name_, base_)\
  class name_ : public base_ {\
    using base_::base_;\
  };

MAKE_EX(WinEx, LuminaException)

#undef MAKE_EX

}