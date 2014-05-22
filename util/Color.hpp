#pragma once
/**
 * \file Color.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file includes LColorCore.hpp, which defines LColor, and provides
 * additional functions for generating a string representation.
 */
#include "ColorCore.hpp"
#include "RepCommon.hpp"

#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>

namespace lumina {

namespace internal {

template <typename T> struct ColorRepTrait;
template <> struct ColorRepTrait<uint8_t> {
  static constexpr const char* name = "Color8";
};
template <> struct ColorRepTrait<uint16_t> {
  static constexpr const char* name = "Color16";
};
template <> struct ColorRepTrait<uint32_t> {
  static constexpr const char* name = "Color32";
};
template <> struct ColorRepTrait<float> {
  static constexpr const char* name = "Color32f";
};
template <> struct ColorRepTrait<half> {
  static constexpr const char* name = "Color16f";
};

}


template <typename T>
std::string colorRep(Color<T, true> in) {
  std::string out(internal::ColorRepTrait<T>::name);
  out += " {";
  out += "r => " + numberToRep(in.r) + ", ";
  out += "g => " + numberToRep(in.g) + ", ";
  out += "b => " + numberToRep(in.b) + ", ";
  out += "a => " + numberToRep(in.a);
  out += "}";
  return out;
}
template <typename T>
std::string colorRep(Color<T, false> in) {
  std::string out(internal::ColorRepTrait<T>::name);
  out += " {";
  out += "r => " + numberToRep(in.r) + ", ";
  out += "g => " + numberToRep(in.g) + ", ";
  out += "b => " + numberToRep(in.b);
  out += "}";
  return out;
}

template <typename T, bool A>
std::ostream& operator<<(std::ostream& out, Color<T, A> in) {
  return (out << colorRep(in));
}

// TODO: find another name
template <typename T>
std::string createColorHexCode(Color<T, true> in) {
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