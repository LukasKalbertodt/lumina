#pragma once

#include "MatrixCore.hpp"
#include "RepCommon.hpp"

#include <string>
#include <sstream>
#include <ostream>

namespace lumina {
namespace internal {

template <typename T, std::size_t Z, std::size_t S>
std::string matrixRep(const Matrix<T, Z, S>& m) {
  std::stringstream ss;
  ss << "Matrix<" << Z << "x" << S << ">" 
     << internal::typeCharRep<T>() << " {";

  for(int i = 0; i < Z; ++i) {
    if(i != 0) {
      ss << ", ";
    }
    ss <<"{";

    for(int j = 0; j < S; ++j) {
      if(j != 0) {
        ss <<", ";
      }
      ss << internal::numberToRep(m.data[i][j]);
    }

    ss << "}";
  }

  ss << "}";
  return ss.str();
}

} // namespace internal

template <typename T, std::size_t Z, std::size_t S>
std::ostream& operator<<(std::ostream& out, const Matrix<T, Z, S>& m) {
  return (out << matrixRep(m));
}

} // namespace lumina
