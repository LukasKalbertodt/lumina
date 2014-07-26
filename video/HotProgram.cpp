#include "HotProgram.hpp"
#include "GLException.hpp"
#include "VertexSeq.hpp"
#include "TextureUnits.hpp"
#include "FrameBuffer.hpp"

#include <vector>
using namespace std;

namespace lumina {

void HotProgram::draw(const HotTexCont& texCont,
                      const VertexSeq& data,
                      PrimitiveType type,
                      int offset,
                      int count) {
  // if textures are used, we need to check the number of textures in the 
  // texture container against the number of currently primed textures
  if(config::debugTextureDrawChecks) {
    if(texCont.count() != TextureUnits::countPrimed()) {
      logThrowGL("[HotProgram] Trying to draw with TextureContainer that "
                 "contains <", texCont.count(), "> textures, but <",
                 TextureUnits::countPrimed(), "> are currently primed!");
    }
  }

  // draw
  drawImpl(data, type, offset, count);
}

void HotProgram::draw(const VertexSeq& data,
                      PrimitiveType type,
                      int offset,
                      int count) {
  // calling draw without texture container -> user don't want to use textures
  // -> we need to make sure, none are primed
  if(config::debugTextureDrawChecks) {
    if(TextureUnits::countPrimed()) {
      logThrowGL("[HotProgram] Trying to draw without a TextureContainer, "
                 "but <", TextureUnits::countPrimed(), "> textures are "
                 "currently primed!");
    }
  }

  // draw
  drawImpl(data, type, offset, count);
}

void HotProgram::drawImpl(const VertexSeq& data,
                          PrimitiveType type,
                          int offset,
                          int count) {
  // check if any FrameBuffer is bound
  if(config::debugDrawFrameBufferCheck) {
    if(!FrameBuffer::isPrimed()) {
      logThrowGL("[HotProgram] Attempt to call draw without a primed "
                 "framebuffer! (forgot to prime the default FrameBuffer?)");
    }
  }

  // bind vertex and index data
  data.bindVAO();

  // if the count parameter was not supplied, we use the whole sequence
  if(count == -1) {
    count = data.size();
  }

  // get the GL type
  GLenum primitiveType = translatePrimitiveType(type);

  // if there is no index buffer -> use gldrawArrays, glDrawElements otherwise
  if(data.nativeIndexHandle() == 0) {
    glDrawArrays(primitiveType, offset, count);
  }
  else {
    glDrawElements(primitiveType, count, GL_UNSIGNED_INT,
                   reinterpret_cast<void*>(sizeof(GLuint) * offset));
  }

  // unbind vertex and index data
  if(config::resetGLState) {
    data.unbindVAO();
  }
}

} // namespace lumina