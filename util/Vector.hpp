#pragma once
/**
 * \file Vector.hpp
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file includes VectorCore.hpp, which defines Vector, and provides 
 * additional functions for generating a string representation.
 *
 * This file is part of the Lumina Graphics Framework.
 */
#include "VectorCore.hpp"
#include "RepCommon.hpp"

#include <ostream>
#include <sstream>
#include <string>

namespace lumina {
namespace internal {

/**
 * \brief Creates a string representation of a Vector
 */
template <typename T, std::size_t N>
std::string vectorRep(Vector<T, N> in) {
  std::stringstream ss;
  ss << "Vec" << N << internal::typeCharRep<T>() << " {";

  for(int i = 0; i < N; ++i) {
    if(i != 0) 
      ss << ", ";

    // handle special case 0 to 3 (x,y,z,w)
    switch(i) {
      case 0: 
        ss << "x => ";
        break;
      case 1:
        ss << "y => ";
        break;
      case 2:
        ss << "z => ";
        break;
      case 3:
        ss << "w => ";
        break;
    }

    // append string representation of the element
    ss << internal::numberToRep(in.data[i]);
  }

  ss << "}";
  return ss.str();
}

} // namespace internal

/**
 * \brief Overloads the stream output operator using vectorRep
 */
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& out, const Vector<T, N>& vec) {
  return (out << vectorRep(vec));
}

} // namespace lumina