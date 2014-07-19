#pragma once
/**
 * \file ContextBase.hpp
 * This file is part of the Lumina Graphic Library.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * ContextBase is an implementation of the lumina base (see 
 * L/core/NullBase.hpp for more information).
 * Each object has a service context and it will use the service associated 
 * with that specific context. It can be used to have different windows or 
 * debug contexts. 
 * Please note that this base saves the context, which is of type 
 * config::ServiceContext (often 8 or 16 bit). This information is at the 
 * beginning of your classes memory layout. Additional padding can consume even
 * more space.
 * If you don't need to configure different services, you can use SingleBase.
 */
#include "../service/ServiceProvider.hpp"

namespace lumina {

class ContextBase {
public:
  ContextBase();
  
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

private:
  config::ServiceContext m_context;
};

}

#include "ContextBase.tpp"