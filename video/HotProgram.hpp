#pragma once

#include "GLObject.hpp"
#include "UniformSet.hpp"
#include "Program.hpp"

namespace lumina {


class HotProgram : public GLObject {
public:
  internal::UniformSet uniform;

  ~HotProgram();

private:
  HotProgram(Program& ref);

  Program& m_cold;

  static bool s_isPrimed;

  friend Program;
};

}

#include "HotProgram.tpp"