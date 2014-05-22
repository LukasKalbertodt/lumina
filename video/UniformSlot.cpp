#include "LGLTools.hpp"
#include "UniformSlot.hpp"
#include "../core/LGLException.hpp"

#include <GL/glew.h>

namespace lumina {
namespace internal {

void UniformSlot::operator=(float val) {
  glUniform1f(index, val);

  // check for error
  auto err = glGetError();
  if(err != GL_NO_ERROR) {
    logError("[UniformSlot] Error while writing float uniform <",
             translateGLError(err),
             ">!");
    throw LGLException("[UniformSlot] Error while writing float uniform");
  }
}

}
}