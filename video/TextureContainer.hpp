#pragma once

#include "HotTexture.hpp"
#include "../util/VariadicTools.hpp"
#include "../util/NotCloneable.hpp"
#include <functional>
#include <map>
#include <type_traits>

namespace lumina {

class TextureContainer : public NotCloneable {
public:
  TextureContainer();

  int count() const;

private:
  std::map<int, int> m_map;
};

using TexCont = TextureContainer;

}

#include "TextureContainer.tpp"