#pragma once

#include "stdexcept"

namespace lumina {

class LVideoDriverException : public std::runtime_error {
  // inherit constructor
  using std::runtime_error::runtime_error;
};

} // namespace lumina