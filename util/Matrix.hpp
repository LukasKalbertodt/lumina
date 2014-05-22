#pragma once

#include "MatrixCore.hpp"
#include "RepCommon.hpp"

#include <string>
#include <ostream>

namespace lumina {

template <typename T, std::size_t Z, std::size_t S>
std::string matrixRep(const Matrix<T, Z, S>& m) {
  std::string out = "Matrix<0x0> {";

  // TODO: maybe fix this ugly %10 hack
  out[8] += Z % 10;
  out[10] += S % 10;

  for(int i = 0; i < Z; ++i) {
    if(i != 0) {
      out += ", ";
    }
    out += "{";

    for(int j = 0; j < S; ++j) {
      if(j != 0) {
        out += ", ";
      }
      out += numberToRep(m.data[i][j]);
    }

    out += "}";
  }

  out += "}";
  return out;
}

template <typename T, std::size_t Z, std::size_t S>
std::ostream& operator<<(std::ostream& out, const Matrix<T, Z, S>& m) {
  return (out << matrixRep(m));
}

};
