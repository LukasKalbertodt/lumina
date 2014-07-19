#include "TextureUnits.hpp"
#include "../service/StaticLogger.hpp"

#include <GL/glew.h>

namespace lumina {

std::vector<bool> TextureUnits::s_primedUnits;
int TextureUnits::s_primedCount = 0;


int getMaxTexUnits() {
  GLint out;
  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &out);
  return out;
}

}