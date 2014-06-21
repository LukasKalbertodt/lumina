#pragma once

#include "../video/Mesh.hpp"
#include "../video/VChan.hpp"
#include "../util/VectorCore.hpp"

namespace lumina {

template <VChan... Chans>
Mesh createBox(Vec3f size);

}

#include "Geometry.tpp"