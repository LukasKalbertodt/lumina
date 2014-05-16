#pragma once

namespace lumina {

enum class LPixelFormat {
  Unknown,

  // RGB formats
  R8,
  R8G8,
  R8G8B8,
  R8G8B8A8,

  // s10e5 formats (16-bits per channel)
  R16F,
  R16G16F,
  R16G16B16A16F,

  // IEEE s23e8 formats (32-bits per channel)
  R32F,
  R32G32F,
  R32G32B32A32F,

  // depth formats
  D16,
  D32,
  D24S8
};

} // namespace lumina