#pragma once
/**
 * \file ContextProxy.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file is included by several files in the engine, 
 * like LServiceProvider.hpp
 * This file MUST:
 * - define a enum type which is in namespace "lumina"
 * - a typedef from the defined enum type to "ServiceContext" in namespace
 *   lumina::config
 * - a value specifying the default value for the service context, named 
 *   "defaultServiceContext", in namespace lumina::config
 * - a value specifying the number of values in the enum, named 
 *   "serviceContextNumValues", also in namespace lumina::config
 */
#include "../core/LServiceContext.hpp"

namespace lumina {
namespace config {
  // enum type of the ServiceContext
  typedef LServiceContext ServiceContext;
  // default service context
  constexpr ServiceContext defaultServiceContext = LServiceContext::Default;
  // service context for static service uses (such as slog())
  constexpr ServiceContext staticServiceContext = LServiceContext::Static;
  // number of possible values for the service context
  constexpr ServiceContext serviceContextNumValues =
      LServiceContext::NUM_VALUES;
}
}