#include "HotProgram.hpp"
#include "GLException.hpp"
#include "VertexSeq.hpp"
#include "TextureUnits.hpp"

#include <vector>
using namespace std;

namespace lumina {

void HotProgram::draw(const HotTexCont& texCont,
                      const VertexSeq& data,
                      PrimitiveType type,
                      int offset,
                      int count) {
  if(config::debugTextureDrawChecks) {
    if(texCont.count() != TextureUnits::countPrimed()) {
      logThrowGL("[HotProgram] Trying to draw with TextureContainer that "
                 "contains <", texCont.count(), "> textures, but <",
                 TextureUnits::countPrimed(), "> are currently primed!");
    }
  }

  data.bindVAO();

  if(count == -1) {
    count = data.size();
  }

  GLenum primitiveType = translatePrimitiveType(type);
  if(data.nativeIndexHandle() == 0) {
    glDrawArrays(primitiveType, offset, count);
  }
  else {
    glDrawElements(primitiveType, count, GL_UNSIGNED_INT,
                   reinterpret_cast<void*>(sizeof(GLuint) * offset));
  }
  data.unbindVAO();
}

} // namespace lumina