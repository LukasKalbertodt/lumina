#include "PrimitiveProcessing.hpp"
#include "../config/LConfig.hpp"

#include <GL/glew.h>

namespace lumina {

void PrimitiveProcessing::bindStage() {
  // set which winding order is the front face
  GLenum frontFace;
  switch(m_frontFace) {
    case FaceOrder::ClockWise: frontFace = GL_CW; break;
    case FaceOrder::CounterClockWise: frontFace = GL_CCW; break;
  }
  glFrontFace(frontFace);

  // set which face to cull
  GLenum cullFace;
  switch(m_cullFace) {
    case CullFace::Front: cullFace = GL_FRONT; break;
    case CullFace::Back: cullFace = GL_BACK; break;
    case CullFace::FrontAndBack: cullFace = GL_FRONT_AND_BACK; break;
  }
  glCullFace(cullFace);

  // enable or disable culling
  if(m_cullEnable) {
    glEnable(GL_CULL_FACE);
  }
  else {
    glDisable(GL_CULL_FACE);
  }
}

void PrimitiveProcessing::unbindStage() {
  if(config::resetGLState) {
    // reset all parameters to the default GL state (should use the constants)
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);
  }
}

} // namespace lumina