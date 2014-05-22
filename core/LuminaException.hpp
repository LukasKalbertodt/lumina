#pragma once

#include <stdexcept>

namespace lumina {

class LuminaException : public std::runtime_error {
  // inherit constructor
  using std::runtime_error::runtime_error;
};

} // namespace lumina