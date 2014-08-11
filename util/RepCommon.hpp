#pragma once
/**
 * \file RepCommon.hpp
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file defines some helper functions for generating string 
 * representations, most of them for internal use only!

 * This file is part of the Lumina Graphics Framework.
 */

#include <string>

namespace lumina {

class half;
namespace internal {
/**
 * @brief Helper function to generate a string from a arbitrary type.
 *        Just for internal use!
 * @details The conversion method is type dependent:
 *          - for integrals: std::to_string
 *          - for floating point types: snprintf with a custom format
 *          - for everything else: trying to static_cast it to string
 * 
 * @param in Value which is converted to std::string
 * @return The string representing the object in
 */
template <typename T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type
numberToRep(T in) {
  return std::to_string(in);
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value
                        && !std::is_same<T, half>::value,
                        std::string>::type
numberToRep(T in) {
  char buf[20];
  std::snprintf(buf, 20, "%g", in);
  return std::string(buf);
}

template <typename T>
typename std::enable_if<std::is_same<T, half>::value, std::string>::type
numberToRep(T in) {
  return numberToRep(static_cast<float>(in));
}

// void numberToRep(half in) {
//   char buf[20];
//   std::snprintf(buf, 20, "%g", in);
//   return std::string(buf);
// }

template <typename T>
typename std::enable_if<!std::is_arithmetic<T>::value, std::string>::type
numberToRep(const T& in) {
  return static_cast<std::string>(in);
}


template <typename T> const char* typeCharRep() { return "?"; }
template <> constexpr const char* typeCharRep<int>() { return "i"; }
template <> constexpr const char* typeCharRep<unsigned int>() { return "ui"; }
template <> constexpr const char* typeCharRep<float>() { return "f"; }
template <> constexpr const char* typeCharRep<double>() { return "d"; }


}
}