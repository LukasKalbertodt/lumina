#pragma once

#include "LuminaException.hpp"

namespace lumina {

class NotReadyEx : public LuminaException {
  // inherit constructor
  using LuminaException::LuminaException;
};

}
