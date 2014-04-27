#pragma once

#include "LVectorCore.hpp"
#include "LColorCore.hpp"

namespace lumina {

template <typename T>
Vec3f colorToVec3f(LColor<T> c) {
  return Vec3f(colorProportion(c.r),
               colorProportion(c.g),  
               colorProportion(c.b));
}
template <typename T>
LVector<T, 4> colorToVec(LColor<T> c) {
  return LVector<T, 4>(c.r, c.g, c.b, c.a);
}

};