#pragma once

#include "../config/ContextProxy.hpp"
#include "Logger.hpp"

namespace lumina {

static Logger& getLoggerService(config::ServiceContext cnt) {
  static Logger instances[static_cast<int>(config::serviceContextNumValues)];
  return instances[static_cast<int>(cnt)];
}

} // namespace lumina