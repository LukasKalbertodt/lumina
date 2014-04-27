#pragma once

#include "LConfig.hpp"

namespace lumina {

class LSingleBase {
  public:
  void setServiceContext(config::ServiceContext cnt) {
  }


protected:
  template <typename... Ts>
  void log(Ts... args) {
    LServiceProvider::getLogger(config::defaultServiceContext).log(args...);
  }
};


}