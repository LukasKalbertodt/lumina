#pragma once

#include "Texture.hpp"
#include "HotTextureContainer.hpp"
#include "../util/VariadicTools.hpp"
#include "../util/NotCloneable.hpp"
#include <functional>
#include <map>
#include <type_traits>

namespace lumina {

class TextureContainer : public NotCloneable {
public:
  TextureContainer();

  void addTexture(int texUnit, const TextureInterface& tex);
  void prime(std::function<void(HotTexCont&)> func);

  int count() const;

private:
  std::map<int, const TextureInterface*> m_texs;
};

using TexCont = TextureContainer;

}

#include "TextureContainer.tpp"