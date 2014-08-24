#pragma once

#include "FrameBuffer.hpp"
#include "GLException.hpp"
#include "GLObject.hpp"
#include "HotProgram.hpp"
#include "HotTextureContainer.hpp"
#include "PrimitiveType.hpp"
#include "Program.hpp"
#include "TextureUnits.hpp"
#include "UniformSet.hpp"
#include "VertexSeq.hpp"

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
  template <typename... Ts>
  void draw(const HotTexCont& texCont,
            const VertexSeq<Ts...>& data,
            PrimitiveType type,
            int offset = 0,
            int count = -1);
  /** Draws a VertexSeq without textures.
  See the other overload of draw() for more information.
  */
  template <typename... Ts>
  void draw(const VertexSeq<Ts...>& data,
            PrimitiveType type,
            int offset = 0,
            int count = -1);

private:
  HotProgram(Program& ref);

  template <typename... Ts>
  void drawImpl(const VertexSeq<Ts...>& data,
                PrimitiveType type,
                int offset = 0,
                int count = -1);

  friend Program;
};

}

#include "HotProgram.tpp"