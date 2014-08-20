#include "PerFragmentProcessing.hpp"

#include "../config/LConfig.hpp"
#include <GL/glew.h>


namespace lumina {

static GLenum blendParamGL(BlendParam param) {
  switch(param) {
    case BlendParam::Zero:      return GL_ZERO;
    case BlendParam::One:       return GL_ONE;
    case BlendParam::SrcColor:  return GL_SRC_COLOR;
    case BlendParam::DstColor:  return GL_DST_COLOR;
  }
}

static GLenum blendFuncGL(BlendFunction func) {
  switch(func) {
    case BlendFunction::Add:                return GL_FUNC_ADD;
    case BlendFunction::Subtract:           return GL_FUNC_SUBTRACT;
    case BlendFunction::ReverseSubtract:    return GL_FUNC_REVERSE_SUBTRACT;
    case BlendFunction::Min:                return GL_MIN;
    case BlendFunction::Max:                return GL_MAX;
  }
}

void PerFragmentProcessing::bindStage() {
  // --------- Set depth test params ------------
  // enable or disable depth test
  if(m_depthEnabled) {
    glEnable(GL_DEPTH_TEST);
  }
  else {
    glDisable(GL_DEPTH_TEST);
  }

  // enable or disable depth write operations
  if(m_depthWrite) {
    glDepthMask(GL_TRUE);
  }
  else {
    glDepthMask(GL_FALSE);
  }

  // set depth function
  GLenum depthFunc;
  switch(m_depthFunc) {
    case DepthFunction::Never:    depthFunc = GL_NEVER; break;
    case DepthFunction::Less:     depthFunc = GL_LESS; break;
    case DepthFunction::Equal:    depthFunc = GL_EQUAL; break;
    case DepthFunction::Lequal:   depthFunc = GL_LEQUAL; break;
    case DepthFunction::Greater:  depthFunc = GL_GREATER; break;
    case DepthFunction::NotEqual: depthFunc = GL_NOTEQUAL; break;
    case DepthFunction::Gequal:   depthFunc = GL_GEQUAL; break;
    case DepthFunction::Always:   depthFunc = GL_ALWAYS; break;
  }
  glDepthFunc(depthFunc);


  // --------- Set blending params ------------
  glBlendEquationSeparate(blendFuncGL(blendFuncRGB), blendFuncGL(blendFuncA));
  glBlendFuncSeparate(blendParamGL(srcRGBParam),
                      blendParamGL(dstRGBParam),
                      blendParamGL(srcAParam),
                      blendParamGL(dstAParam));

}

void PerFragmentProcessing::unbindStage() {
  if(config::resetGLState) {
    // reset parameter for depth testing
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
  }
}


}