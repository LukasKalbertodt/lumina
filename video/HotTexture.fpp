#pragma once

#include "TexType.hpp"

namespace lumina {

template <TexType TT> class HotTexture;
  
using HotTex2D = HotTexture<TexType::Tex2D>;
using HotTex3D = HotTexture<TexType::Tex3D>;
using HotTexCube = HotTexture<TexType::Cube>;

}