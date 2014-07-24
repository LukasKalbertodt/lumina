#pragma once

#include "Texture.hpp"
#include "HotTextureContainer.hpp"
#include "GLObject.hpp"
#include "../util/VariadicTools.hpp"
#include "../util/NotCloneable.hpp"
#include <functional>
#include <map>
#include <type_traits>

namespace lumina {

class TextureContainer : public GLObject {
public:
  TextureContainer();

  void addTexture(int texUnit, TextureInterface& tex);
  void prime(std::function<void(HotTexCont&)> func);

  int count() const;

private:
  std::map<int, TextureInterface*> m_texs;
};

using TexCont = TextureContainer;

}

#include "TextureContainer.tpp"