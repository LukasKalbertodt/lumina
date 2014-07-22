#include "GLObject.hpp"
#include "RenderContext.hpp"

namespace lumina {

bool GLObject::isRenderContextCurrent() {
  return RenderContext::isContextCurrent();
}


}