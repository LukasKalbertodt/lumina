#pragma once

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