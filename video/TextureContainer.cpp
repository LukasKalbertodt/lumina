#include "TextureContainer.hpp"

namespace lumina {

void TextureContainer::addTexture(int texUnit, TextureInterface& tex) {
  if(m_texs.count(texUnit) > 0) {
    logNotice("[TextureContainer] Called addTexture with a texture unit<", 
              texUnit, "> that is already in use (will be overwritten)...");
  }
  m_texs[texUnit] = &tex;
}

void TextureContainer::prime(std::function<void(HotTexCont&)> func) {
  // iterate through all {texUnit, tex} pairs and prepare the textures
  for(auto p : m_texs) {
    p.second->prePrime(p.first);
  }

  // create HotTexCont and call function

  // iterate through all {texUnit, tex} pairs and do cleanup/unprime
  for(auto p : m_texs) {
    p.second->postPrime(p.first);
  }
}


}