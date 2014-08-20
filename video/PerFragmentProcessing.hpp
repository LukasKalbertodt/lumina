#pragma once

#include "Program.fpp"
#include "../util/NotCloneable.hpp"

#include <cstdint>

namespace lumina {

enum class DepthFunction : std::uint8_t {
  Never, Less, Equal, Lequal, Greater, NotEqual, Gequal, Always
};

enum class BlendFunction : std::uint8_t {
  Add, Subtract, ReverseSubtract, Min, Max
};

enum class BlendParam : std::uint8_t {
  Zero,
  One,
  SrcAlpha,
  SrcColor,
  DstAlpha,
  DstColor,
  OneMinusSrcAlpha,
  OneMinusSrcColor,
  OneMinusDstAlpha,
  OneMinusDstColor
};


class PerFragmentProcessing : public NotCopyable {
public:
  PerFragmentProcessing();

  void enableDepthTest(bool enable = true);
  void enableDepthWrite(bool enable = true);
  void setDepthFunction(DepthFunction func);

  // void setBlendFunction(BlendFunction funcRGB, BlendFunction funcA);
  // void setBlendParamsRGB(BlendParam src, BlendParam dst);
  // void setBlendParamA(BlendParam src, BlendParam dst);

  BlendFunction blendFuncRGB;
  BlendFunction blendFuncA;
  BlendParam srcRGBParam;
  BlendParam dstRGBParam;
  BlendParam srcAParam;
  BlendParam dstAParam;

private:
  bool m_depthEnabled;
  bool m_depthWrite;
  DepthFunction m_depthFunc;




  void bindStage();
  void unbindStage();

  friend Program;
};

}

#include "PerFragmentProcessing.tpp"