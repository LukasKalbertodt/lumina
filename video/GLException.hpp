#pragma once

#include "../core/LuminaException.hpp"

namespace lumina {

class GLException : public LuminaException {
  // inherit constructor
  using LuminaException::LuminaException;
};

} // namespace lumina