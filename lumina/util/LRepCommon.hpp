#pragma once
/**
 * \file LRepCommon.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file defines some helper functions for generating string 
 * representations, most of them for internal use only!
 */

namespace lumina {
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
lxNumericFormat(T in) {
  return std::to_string(in);
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, std::string>::type
lxNumericFormat(T in) {
  char buf[20];
  std::snprintf(buf, 20, "%g", in);
  return std::string(buf);
}

template <typename T>
typename std::enable_if<!std::is_arithmetic<T>::value, std::string>::type
lxNumericFormat(const T& in) {
  return static_cast<std::string>(in);
}

}