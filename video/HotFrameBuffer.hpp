#pragma once

#include "HotFrameBuffer.fpp"
#include "FrameBuffer.hpp"
#include "GLObject.hpp"
#include "../util/NotCloneable.hpp"
#include "../util/ColorCore.hpp"

#include <memory>

namespace lumina {

// class HotFrameBufferInterface : public GLObject {
// public:



// };

class HotFrameBuffer : public GLObject {
public:
  HotFrameBuffer(std::shared_ptr<internal::FrameBufferInterface> cold);

  // internal::HotColorAttSet colors;

private:
  std::shared_ptr<internal::FrameBufferInterface> m_cold;
};

} // namespace lumina 

#include "HotFrameBuffer.tpp"