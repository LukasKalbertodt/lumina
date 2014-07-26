#pragma once

#include "GLObject.hpp"
#include "UniformSet.hpp"
#include "Program.hpp"
#include "VertexSeq.fpp"
#include "PrimitiveType.hpp"
#include "HotTextureContainer.hpp"

namespace lumina {


class HotProgram : public GLObject {
public:
  internal::UniformSet uniform;

  void draw(const HotTexCont& texCont,
            const VertexSeq& data,
            PrimitiveType type,
            int offset = 0,
            int count = -1);
  void draw(const VertexSeq& data,
            PrimitiveType type,
            int offset = 0,
            int count = -1);

private:
  HotProgram(Program& ref);

  void drawImpl(const VertexSeq& data,
                PrimitiveType type,
                int offset = 0,
                int count = -1);

  friend Program;
};

}

#include "HotProgram.tpp"