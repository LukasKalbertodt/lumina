#pragma once

#include "HotRenderContext.fpp"
#include "GLProperty.hpp"
#include "RenderContext.hpp"
#include "GLObject.hpp"
#include "../util/NotCloneable.hpp"

namespace lumina {

class HotRenderContext : public GLContextFreeObject {
public:
  HotRenderContext(RenderContext& cold);
  ~HotRenderContext();

  FrameBuffer& getDefaultFrameBuffer();
  void swapBuffer();

  template <typename T = int> T getProperty(GLProp prop);

private:
  RenderContext& m_cold;
};

}

#include "HotRenderContext.tpp"