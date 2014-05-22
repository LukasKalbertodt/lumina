#include "GLException.hpp"
#include "GLTools.hpp"
#include "UniformSlot.hpp"

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
    throw GLException("[UniformSlot] Error while writing float uniform");
  }
}

}
}