#pragma once

#include "HotTexture.hpp"
#include "TextureContainer.fpp"
#include "../util/VariadicTools.hpp"
#include "../util/NotCloneable.hpp"
#include <type_traits>

namespace lumina {

class HotTextureContainer : public NotCloneable {
public:
  template <TexType... Ts> HotTextureContainer(const HotTexture<Ts>&... texs);

  int count() const;

private:
  int m_count;

  HotTextureContainer(int count);

  friend TextureContainer;
};

using HotTexCont = HotTextureContainer;

}

#include "HotTextureContainer.tpp"