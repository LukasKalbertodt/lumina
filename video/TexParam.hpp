#pragma once

#include <cstdint>

namespace lumina {


enum class TexWrapMode : uint8_t {
  Repeat, MirrorRepeat, Clamp
};

enum class TexFilterMode : uint8_t {
  Nearest, Linear, Bilinear, Trilinear
};


struct TexParam {
  TexWrapMode wrapMode;
  TexFilterMode filterMode;
  uint8_t anisotropyLevel;
  bool useMipMaps;

  TexParam()
    : wrapMode(TexWrapMode::Repeat),
      filterMode(TexFilterMode::Nearest),
      anisotropyLevel(0) {}
};


}