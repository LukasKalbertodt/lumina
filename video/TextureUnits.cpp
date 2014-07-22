#include "TextureUnits.hpp"
#include "../service/StaticLogger.hpp"
#include "HotRenderContext.hpp"

#include <GL/glew.h>

namespace lumina {

std::vector<bool> TextureUnits::s_primedUnits;
int TextureUnits::s_primedCount = 0;


int getMaxTexUnits() {
  return RenderContext::getCurrentContext().getProperty(
    GLProp::MaxCombinedTextureImageUnits);
}

}