#pragma once

#include "../video/VertexSeq.hpp"
#include "../video/HotVertexSeq.hpp"
#include "../video/VertexAttribute.hpp"
#include "../util/VectorCore.hpp"

namespace lumina {

template <VAttr... Chans>
VertexSeq createBox(Vec3f size);

} // namespace lumina

#include "Geometry.tpp"