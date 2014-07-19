#pragma once

#include "HotFrameBuffer.fpp"
#include "FrameBuffer.hpp"
#include "GLObject.hpp"
#include "HotFBAttPoints.hpp"
#include "../util/NotCloneable.hpp"
#include "../util/ColorCore.hpp"

namespace lumina {

class HotFrameBuffer : public GLObject {
public:
  HotFrameBuffer(FrameBuffer& cold);
  ~HotFrameBuffer();

  internal::HotColorAttSet colors;

private:
  FrameBuffer& m_cold;
};

} // namespace lumina 

#include "HotFrameBuffer.tpp"