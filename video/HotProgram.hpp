#pragma once

#include "GLObject.hpp"
#include "UniformSet.hpp"
#include "Program.hpp"
#include "VertexSeq.fpp"
#include "PrimitiveType.hpp"
#include "HotTextureContainer.hpp"

namespace lumina {

/** Hot version of Program.
Represents a Program that is currently active, which means: All pipeline stages
are active and will be used. You need a HotProgram to draw anything.

\see Program
*/
class HotProgram : public GLObject {
public:
  /// Uniform variables of the current Program
  internal::UniformSet uniform;

  /** Draws a VertexSeq with one or more textures.
  Sends all vertices of the sequence into the pipeline to process them. OpenGL
  processes them as primitives of the type specified.

  \param texCont A HotTexCont containing one or more textures. A Shader can 
  only access the textures in this container.
  \param data The VertexSeq whose vertices will be drawn.
  \param type The PrimitiveType of the vertex data.
  \param offset Offset in the vertex sequence (default 0).
  \param count Specifies how many vertices out of the sequence are used. The
  default value (-1) causes the whole vertex sequence to be drawn.
  */
  void draw(const HotTexCont& texCont,
            const VertexSeq& data,
            PrimitiveType type,
            int offset = 0,
            int count = -1);
  /** Draws a VertexSeq without textures.
  See the other overload of draw() for more information.
  */
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