#pragma once

#include "HotFrameBuffer.fpp"
#include "FrameBuffer.hpp"
#include "GLObject.hpp"
#include "../util/NotCloneable.hpp"

namespace lumina {

class HotFrameBuffer : public GLObject {
public:
  HotFrameBuffer(FrameBuffer& cold);

private:
  // FrameBuffer& m_cold;
};

} // namespace lumina 

#include "HotFrameBuffer.tpp"