#pragma once

#include "LVideoDriverException.hpp"

namespace lumina {

class LGLException : public LVideoDriverException {
  // inherit constructor
  using LVideoDriverException::LVideoDriverException;
};

} // namespace lumina