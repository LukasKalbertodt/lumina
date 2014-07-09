#pragma once

#include "ServiceProvider.hpp"
#include "Logger.hpp"
#include "../config/ContextProxy.hpp"

namespace lumina {

template <typename... Ts>
void slog(Ts... msgs) {
  getLoggerService(config::staticServiceContext).log(msgs...);
}

template <typename... Ts>
void slogWarning(Ts... msgs) {
  getLoggerService(config::staticServiceContext).logWarning(msgs...);
}

template <typename... Ts>
void slogError(Ts... msgs) {
  getLoggerService(config::staticServiceContext).logError(msgs...);
}

}