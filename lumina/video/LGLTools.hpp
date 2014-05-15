#pragma once

#include "GL/glew.h"

namespace lumina {

inline const char* translateGLError(GLenum error) {
  switch(error) {
    case GL_NO_ERROR:           return "GL_NO_ERROR";
    case GL_INVALID_ENUM:       return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:      return "GL_INVALID_VALUE";
    case GL_OUT_OF_MEMORY:      return "GL_OUT_OF_MEMORY";
    case GL_INVALID_OPERATION:  return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";
  }
  return "invalid-error";
}

}