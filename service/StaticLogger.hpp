#pragma once

#include "ServiceProvider.hpp"
#include "Logger.hpp"
#include "../config/ContextProxy.hpp"

namespace lumina {

template <typename... Ts> void slogCritical(Ts... args);
template <typename... Ts> void slogError(Ts... args);
template <typename... Ts> void slogWarning(Ts... args);
template <typename... Ts> void slogNotice(Ts... args);
template <typename... Ts> void slog(Ts... args);
template <typename... Ts> void slogDebug(Ts... args);

}

#include "StaticLogger.tpp"