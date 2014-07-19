#pragma once
/**
 * \file SingleBase.hpp
 * This file is part of the Lumina Graphic Library.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * SingleBase is an implementation of the lumina base (see 
 * L/core/NullBase.hpp for more information).
 * It uses the service of the config::defaultServiceContext. You can think of
 * the ServiceProvider as a Singleton. So every object will use the same 
 * service.
 * If you need to configure different services, you can use ContextBase.
 */
#include "../service/ServiceProvider.hpp"

namespace lumina {

class SingleBase {
public:
  void setServiceContext(config::ServiceContext cnt);

protected:
  template <typename... Ts> void logCritical(Ts... args);
  template <typename... Ts> void logError(Ts... args);
  template <typename... Ts> void logWarning(Ts... args);
  template <typename... Ts> void logNotice(Ts... args);
  template <typename... Ts> void log(Ts... args);
  template <typename... Ts> void logDebug(Ts... args);

  template <typename Ex, LogLevel LL = LogLevel::Error, typename... Ts>
  void logAndThrow(Ts... args);
};

}

#include "SingleBase.tpp"