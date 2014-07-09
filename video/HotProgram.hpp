#pragma once

#include "GLObject.hpp"
#include "UniformSet.hpp"
#include "Program.hpp"
#include "HotVertexSeq.fpp"
#include "PrimitiveType.hpp"

namespace lumina {


class HotProgram : public GLObject {
public:
  internal::UniformSet uniform;

  template <typename... Ts>
  void draw(const HotVertexSeq<Ts...>& data,
            PrimitiveType type,
            int offset,
            int count);

  ~HotProgram();

private:
  HotProgram(Program& ref);

  Program& m_cold;

  static bool s_isPrimed;

  friend Program;
};

}

#include "HotProgram.tpp"