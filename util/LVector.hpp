#pragma once
/**
 * \file LVector.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file includes LVectorCore.hpp, which defines LVector, and provides 
 * additional functions for generating a string representation.
 */
#include "LVectorCore.hpp"
#include "LRepCommon.hpp"

#include <string>
#include <ostream>

namespace lumina {

/**
 * @brief Creates a string representation of a LVector
 */
template <typename T, std::size_t N>
std::string vectorRep(LVector<T, N> in) {
  // TODO: add type here
  std::string out("LVecN {");
  out[4] = '0' + (N % 10);

  for(int i = 0; i < N; ++i) {
    if(i != 0) 
      out += ", ";

    // handle special case 0 to 3 (x,y,z,w)
    switch(i) {
      case 0: 
        out += "x => ";
        break;
      case 1:
        out += "y => ";
        break;
      case 2:
        out += "z => ";
        break;
      case 3:
        out += "w => ";
        break;
    }

    // append string representation of the element
    out += lxNumericFormat(in.data[i]);
  }
  return out + "}";
}

/**
 * @brief Overloads the stream output operator using vectorRep
 */
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& out, const LVector<T, N>& vec) {
  return (out << vectorRep(vec));
}

} // namespace lumina