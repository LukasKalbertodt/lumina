#pragma once

#include "HotRenderContext.fpp"
#include "RenderContext.hpp"
#include "../util/NotCloneable.hpp"

namespace lumina {

class HotRenderContext : public NotCopyable {
public:
  HotRenderContext(RenderContext& cold);
  ~HotRenderContext();
  
  FrameBuffer& getDefaultFrameBuffer();
  void swapBuffer();


private:
  RenderContext& m_cold;

};

}

#include "HotRenderContext.tpp"