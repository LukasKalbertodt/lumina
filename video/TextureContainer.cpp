#include "TextureContainer.hpp"

namespace lumina {

void TextureContainer::addTexture(int texUnit, const TextureInterface& tex) {
  m_texs[texUnit] = &tex;
}

void prime(std::function<void(HotTexCont&)> func) {
  
}


}