#pragma once
/**
 * \file LColor.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file includes LColorCore.hpp, which defines LColor, and provides
 * additional functions for generating a string representation.
 */
#include "LColorCore.hpp"
#include "LRepCommon.hpp"

#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>

namespace lumina {

template <typename T> struct LXColorRepTrait;
template <> struct LXColorRepTrait<uint8_t> {
  static constexpr const char* name = "Color8";
};
template <> struct LXColorRepTrait<uint16_t> {
  static constexpr const char name[] = "Color16";
};
template <> struct LXColorRepTrait<uint32_t> {
  static constexpr const char name[] = "Color32";
};
template <> struct LXColorRepTrait<float> {
  static constexpr const char name[] = "Color32f";
};
template <> struct LXColorRepTrait<half> {
  static constexpr const char name[] = "Color16f";
};


template <typename T>
std::string colorRep(LColor<T> in) {
  std::string out(LXColorRepTrait<T>::name);
  out += " {";
  out += "r => " + lxNumericFormat(in.r) + ", ";
  out += "g => " + lxNumericFormat(in.g) + ", ";
  out += "b => " + lxNumericFormat(in.b) + ", ";
  out += "a => " + lxNumericFormat(in.a);
  out += "}";
  return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, LColor<T> in) {
  return (out << colorRep(in));
}

template <typename T>
std::string createColorHexCode(LColor<T> in) {
  auto col = color_cast<Color8>(in);

  std::stringstream str;
  str << std::hex << std::setfill('0');
  str << std::setw(2) << +col.r;
  str << std::setw(2) << +col.g;
  str << std::setw(2) << +col.b;
  if(col.a != 255) 
    str << std::setw(2) << +col.a;

  return str.str();
}

} // namespace lumina