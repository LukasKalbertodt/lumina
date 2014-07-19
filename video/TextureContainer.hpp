#pragma once

#include "HotTexture.hpp"
#include "../util/VariadicTools.hpp"
#include "../util/NotCloneable.hpp"
#include <type_traits>

namespace lumina {

class TextureContainer : public NotCloneable {
public:
  template <TexType... Ts> TextureContainer(const HotTexture<Ts>&... texs);

  int count() const;

private:
  int m_count;
};

using TexCont = TextureContainer;

}

#include "TextureContainer.tpp"