#pragma once

namespace lumina {

class LRenderContext {
public:
  virtual void create() = 0;
  virtual void makeCurrent() = 0;
  virtual void swapBuffer() = 0;

  virtual ~LRenderContext() = default;
};

} // namespace lumina