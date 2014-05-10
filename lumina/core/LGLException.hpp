#pragma once

#include "LException.hpp"

namespace lumina {

class LGLException : public LException {
  // inherit constructor
  using LException::LException;
};

} // namespace lumina