#pragma once

#include "GLObject.hpp"
#include "UniformSet.hpp"
#include "Program.hpp"
#include "VertexSeq.fpp"
#include "PrimitiveType.hpp"
#include "TextureContainer.hpp"

namespace lumina {


class HotProgram : public GLObject {
public:
  internal::UniformSet uniform;

  void draw(const TexCont& texCont,
            const VertexSeq& data,
            PrimitiveType type,
            int offset = 0,
            int count = -1);

private:
  HotProgram(Program& ref);

  friend Program;
};

}

#include "HotProgram.tpp"