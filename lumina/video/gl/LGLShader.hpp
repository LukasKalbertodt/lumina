#pragma once

#include "../LShader.hpp"

namespace lumina {

class LGLShader : public LShader {
public:
  void compile() {
    log("Now compiling (GL)!");
  }
};


} // namespace lumina