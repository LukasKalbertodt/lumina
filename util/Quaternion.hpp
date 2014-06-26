#pragma once
/**
 * \file Quaternion.hpp
 * This file is part of the Lumina Graphics Framework.
 *
 * \author Julian Kniephoff <julian.kniephoff@gmail.com>
 *
 * This file includes QuaternionCore.hpp, which defines Quaternion,
 * and provides additional functions for generating quaternions
 * and string representations.
 */
#include "QuaternionCore.hpp"
#include "RepCommon.hpp"

#include <cmath>
#include <string>
#include <ostream>

namespace lumina {

template <typename T, typename S>
auto quaternionFromAxisAngle(Vec3<T> axis, S angle)
    -> Quaternion<decltype(T(0) * std::sin(S(0)))> {
  Quaternion<decltype(T(0) * std::sin(S(0)))> q;
  S a2 = angle / 2;
  auto sa2 = std::sin(a2);

  q.w = std::cos(a2);
  q.x = axis.x * sa2;
  q.y = axis.y * sa2;
  q.z = axis.z * sa2;

  return q;
}

template <typename T>
std::string quaternionRep(Quaternion<T> in) {
  std::string out("Quaternion: ");
  out += internal::numberToRep(in.w);
  out += " + " + internal::numberToRep(in.x) + " * i";
  out += " + " + internal::numberToRep(in.y) + " * j";
  out += " + " + internal::numberToRep(in.z) + " * k";
  return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Quaternion<T> q) {
  return (out << quaternionRep(q));
}

}