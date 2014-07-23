#pragma once

#include "Program.fpp"
#include <cstdint>

namespace lumina {

enum class FaceOrder : uint8_t {
  ClockWise, CounterClockWise
};

enum class CullFace : uint8_t {
  Front, Back, FrontAndBack
};

namespace constants {
  constexpr FaceOrder DefaultFrontFace = FaceOrder::CounterClockWise;
  constexpr CullFace DefaultCullFace = CullFace::Back;
  constexpr bool DefaultCullEnable = false;
}

class PrimitiveProcessing {
public:
  PrimitiveProcessing();

  void enableCulling();
  void disableCulling();
  void setFrontFace(FaceOrder order);
  void setCullFace(CullFace face);

private:
  FaceOrder m_frontFace;
  CullFace m_cullFace;
  bool m_cullEnable;

  void bindStage();
  void unbindStage();

  friend Program;
};

} // namespace lumina 

#include "PrimitiveProcessing.tpp"