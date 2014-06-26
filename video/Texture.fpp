#pragma once

#include "TexType.hpp"

namespace lumina {

template <TexType TT> class Texture;

using Tex2D = Texture<TexType::Tex2D>;
using Tex3D = Texture<TexType::Tex3D>;
using TexCube = Texture<TexType::Cube>;
  
}
