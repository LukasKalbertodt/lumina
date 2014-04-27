#pragma once
/**
 * \file LSingleBase.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * LSingleBase is an implementation of the lumina base (see 
 * L/core/LNullBase.hpp for more information).
 * It uses the service of the config::defaultServiceContext. You can think of
 * the ServiceProvider as a Singleton. So every object will use the same 
 * service.
 * If you need to configure different services, you can use LContextBase.
 */
#include "LConfig.hpp"

namespace lumina {

class LSingleBase {
public:
  void setServiceContext(config::ServiceContext cnt) {}


protected:
  template <typename... Ts>
  void log(Ts... args) {
    LServiceProvider::getLogger(config::defaultServiceContext).log(args...);
  }

  template <typename... Ts>
  void logError(Ts... args) {
    LServiceProvider::getLogger(config::defaultServiceContext)
      .logError(args...);
  }

  template <typename... Ts>
  void logWarning(Ts... args) {
    LServiceProvider::getLogger(config::defaultServiceContext)
      .logWarning(args...);
  }
};


}