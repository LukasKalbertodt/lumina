#pragma once

#include "../video/VertexSeq.hpp"
#include "../video/HotVertexSeq.hpp"
#include "../video/VChan.hpp"
#include "../util/VectorCore.hpp"

namespace lumina {

template <VChan... Chans>
VertexSeq createBox(Vec3f size);

}

#include "Geometry.tpp"