#pragma once

#include "gl/LGLShader.hpp"

namespace lumina {

template <typename T>
struct LDriverTraits;

template <>
struct LDriverTraits<class LShader> {
  typedef class LGLShader GLType;
  typedef class LDXShader DXType;
};

} // namespace lumina