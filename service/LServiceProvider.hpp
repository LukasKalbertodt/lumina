#pragma once

#include "../config/ContextProxy.hpp"
#include "LLogger.hpp"

namespace lumina {

class LServiceProvider {
public:

  static LLogger& getLogger(config::ServiceContext cnt) {
    static LLogger instances[static_cast<int>(config::serviceContextNumValues)];
    return instances[static_cast<int>(cnt)];
  }


private:
  
};


} // namespace lumina