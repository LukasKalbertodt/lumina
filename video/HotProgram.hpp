#pragma once

#include "GLObject.hpp"
#include "UniformSet.hpp"
#include "Program.hpp"
#include "VertexSeq.fpp"
#include "PrimitiveType.hpp"

namespace lumina {


class HotProgram : public GLObject {
public:
  internal::UniformSet uniform;

  void draw(const VertexSeq& data,
            PrimitiveType type,
            int offset = 0,
            int count = -1);

  ~HotProgram();

private:
  HotProgram(Program& ref);

  Program& m_cold;

  static bool s_isPrimed;

  friend Program;
};

}

#include "HotProgram.tpp"