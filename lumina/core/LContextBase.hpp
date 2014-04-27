#pragma once
/**
 * \file LContextBase.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * LContextBase is an implementation of the lumina base (see 
 * L/core/LNullBase.hpp for more information).
 * Each object has a service context and it will use the service associated 
 * with that specific context. It can be used to have different windows or 
 * debug contexts. 
 * Please note that this base saves the context, which is of type 
 * config::ServiceContext (often 8 or 16 bit). This information is at the 
 * beginning of your classes memory layout. Additional padding can consume even
 * more space.
 * If you don't need to configure different services, you can use LSingleBase.
 */
#include "../service/LServiceProvider.hpp"

namespace lumina {

class LContextBase {
public:
  LContextBase() 
    : m_context(config::defaultServiceContext) 
  {}
  
  void setServiceContext(config::ServiceContext cnt) {
    m_context = cnt;
  }


protected:
  template <typename... Ts>
  void log(Ts... args) {
    LServiceProvider::getLogger(m_context).log(args...);
  }

  template <typename... Ts>
  void logError(Ts... args) {
    LServiceProvider::getLogger(m_context).logError(args...);
  }

  template <typename... Ts>
  void logWarning(Ts... args) {
    LServiceProvider::getLogger(m_context).logWarning(args...);
  }



private:
  config::ServiceContext m_context;
};

}