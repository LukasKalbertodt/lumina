#pragma once

#include "../video/VertexSeq.hpp"
#include "../video/HotVertexSeq.hpp"
#include "../video/VertexAttribute.hpp"
#include "../util/VectorCore.hpp"

namespace lumina {

/**
 * \brief Creates a VertexSeq that represents a box.
 * 
 * \param size The size of the box in each direction
 * \tparam Chans A list of VertexAttributes that should be written per vertex
 */
template <VAttr... Chans>
VertexSeq<typename internal::VAttrHelper<Chans>::type...> createBox(Vec3f size);

template <VAttr... Chans>
VertexSeq<typename internal::VAttrHelper<Chans>::type...> createSphere(
  float radius, int thetaSteps, int phiSteps);

} // namespace lumina

#include "Geometry.tpp"