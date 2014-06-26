#pragma once

#include "LServiceProvider.hpp"
#include "LLogger.hpp"
#include "../config/ContextProxy.hpp"

namespace lumina {

template <typename... Ts>
void slog(Ts... msgs) {
  LServiceProvider::getLogger(config::staticServiceContext).log(msgs...);
}

template <typename... Ts>
void slogWarning(Ts... msgs) {
  LServiceProvider::getLogger(config::staticServiceContext).logWarning(msgs...);
}

template <typename... Ts>
void slogError(Ts... msgs) {
  LServiceProvider::getLogger(config::staticServiceContext).logError(msgs...);
}

}