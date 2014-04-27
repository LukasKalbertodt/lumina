#pragma once
#include "../config/BaseProxy.hpp"

namespace lumina {

class LShader : public config::CommonBase {
public:
  virtual void compile() = 0;
};

}