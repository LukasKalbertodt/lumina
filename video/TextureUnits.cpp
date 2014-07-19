#include "TextureUnits.hpp"
#include "../service/StaticLogger.hpp"

#include <GL/glew.h>

namespace lumina {

std::vector<bool> TextureUnits::s_primedUnits;

bool TextureUnits::isPrimed(int index) {
  init();
  return s_primedUnits[index];
}

void TextureUnits::setPrimed(int index) {
  init();
  s_primedUnits[index] = true;
}

void TextureUnits::unsetPrimed(int index) {
  init();
  s_primedUnits[index] = false;
}

void TextureUnits::init() {
  static bool ready = false;
  if(!ready) {
    slog("I'm in, Jonny!");
    s_primedUnits.resize(getMaxTexUnits());
    ready = true;
  }
}


int getMaxTexUnits() {
  GLint out;
  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &out);
  return out;
}

}