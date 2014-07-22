#pragma once
/**
 * \file MatrixCore.hpp
 * This file is part of the Lumina Graphics Framework.
 *
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * \author Sebastian von Ohr
 *
 * This file will define Matrix and various matrix functions. In most cases you
 * should include Matrix.hpp instead, which provides additional helper
 * functions (but has more dependencies).
 * This file also depends on VectorCore.hpp!
 */

#include "VectorCore.hpp"

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <xmmintrin.h>

namespace lumina {

namespace internal {
/*******************************************************************************
* Internal Helper: The following is for internal use only!
*******************************************************************************/
/**
 * @brief Helper struct for various algorithms. Just for internal use!
 */
template <typename T>
class MatrixHelper {
  // if a determinant is smaller than this value, it's treated as zero
  static constexpr float detEpsilon = 1E-10;

public:
  /**
   * @brief calculates the determinant of the matrix
   */
  template <std::size_t N>
  static T det(const T (&m)[N][N]) {
    throw std::runtime_error("Not implemented!");
  }

  // overload for 2x2 matrix
  static T det(const T (&m)[2][2]) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
  }

  // overload for 3x3 matrix
  static T det(const T (&m)[3][3]) {
    return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0]
           + m[0][2] * m[1][0] * m[2][1] - m[0][2] * m[1][1] * m[2][0]
           - m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][2] * m[2][1];
  }

  // overload for 4x4 matrix
  static T det(const T (&m)[4][4]) {
    float s0 = m[0][0] * m[1][1] - m[1][0] * m[0][1];
    float s1 = m[0][0] * m[1][2] - m[1][0] * m[0][2];
    float s2 = m[0][0] * m[1][3] - m[1][0] * m[0][3];
    float s3 = m[0][1] * m[1][2] - m[1][1] * m[0][2];
    float s4 = m[0][1] * m[1][3] - m[1][1] * m[0][3];
    float s5 = m[0][2] * m[1][3] - m[1][2] * m[0][3];

    float c5 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    float c4 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    float c3 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    float c2 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    float c1 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    float c0 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

    return (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);
  }

  /**
   * @brief calculates the inverted matrix and writes it to out
   * 
   * @param m matrix to invert
   * @param out out-parameter for inverted matrix
   */
  template <std::size_t N>
  static void invert(const T (&m)[N][N], T (&out)[N][N]) {
    throw std::runtime_error("Not implemented!");
  }

  // overload für 2x2 matrix
  static void invert(const T (&m)[2][2], T (&out)[2][2]) {
    float det = det(m);
    if(fabs(det) < detEpsilon) {
      throw std::runtime_error("Matrix is not invertable: Determinant is "
        "smaller than epsilon");
    }

    float invdet = 1.f / det;

    out[0][0] =  m[1][1] * invdet;
    out[0][1] = -m[0][1] * invdet;
    out[1][0] = -m[1][0] * invdet;
    out[1][1] =  m[0][0] * invdet;
  }

  // overload for 3x3 matrix
  static void invert(const T (&m)[3][3], T (&out)[3][3]) {
    float det = det(m);
    if(fabs(det) < detEpsilon) {
      throw std::runtime_error("Matrix is not invertable: Determinant is "
        "smaller than epsilon");
    }

    float invdet = 1.f / det;

    out[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invdet;
    out[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invdet;
    out[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;

    out[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invdet;
    out[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invdet;
    out[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * invdet;

    out[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invdet;
    out[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * invdet;
    out[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invdet;
  }

  // overload for 4x4 matrix
  static void invert(const T (&m)[4][4], T (&out)[4][4]) {
    float s0 = m[0][0] * m[1][1] - m[1][0] * m[0][1];
    float s1 = m[0][0] * m[1][2] - m[1][0] * m[0][2];
    float s2 = m[0][0] * m[1][3] - m[1][0] * m[0][3];
    float s3 = m[0][1] * m[1][2] - m[1][1] * m[0][2];
    float s4 = m[0][1] * m[1][3] - m[1][1] * m[0][3];
    float s5 = m[0][2] * m[1][3] - m[1][2] * m[0][3];

    float c5 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    float c4 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    float c3 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    float c2 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    float c1 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    float c0 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

    float det = (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);
    if(fabs(det) < detEpsilon) {
      throw std::runtime_error("Matrix is not invertable: Determinant is "
        "smaller than epsilon");
    }

    float invdet = 1.f / det;

    out[0][0] = ( m[1][1] * c5 - m[1][2] * c4 + m[1][3] * c3) * invdet;
    out[0][1] = (-m[0][1] * c5 + m[0][2] * c4 - m[0][3] * c3) * invdet;
    out[0][2] = ( m[3][1] * s5 - m[3][2] * s4 + m[3][3] * s3) * invdet;
    out[0][3] = (-m[2][1] * s5 + m[2][2] * s4 - m[2][3] * s3) * invdet;

    out[1][0] = (-m[1][0] * c5 + m[1][2] * c2 - m[1][3] * c1) * invdet;
    out[1][1] = ( m[0][0] * c5 - m[0][2] * c2 + m[0][3] * c1) * invdet;
    out[1][2] = (-m[3][0] * s5 + m[3][2] * s2 - m[3][3] * s1) * invdet;
    out[1][3] = ( m[2][0] * s5 - m[2][2] * s2 + m[2][3] * s1) * invdet;

    out[2][0] = ( m[1][0] * c4 - m[1][1] * c2 + m[1][3] * c0) * invdet;
    out[2][1] = (-m[0][0] * c4 + m[0][1] * c2 - m[0][3] * c0) * invdet;
    out[2][2] = ( m[3][0] * s4 - m[3][1] * s2 + m[3][3] * s0) * invdet;
    out[2][3] = (-m[2][0] * s4 + m[2][1] * s2 - m[2][3] * s0) * invdet;

    out[3][0] = (-m[1][0] * c3 + m[1][1] * c1 - m[1][2] * c0) * invdet;
    out[3][1] = ( m[0][0] * c3 - m[0][1] * c1 + m[0][2] * c0) * invdet;
    out[3][2] = (-m[3][0] * s3 + m[3][1] * s1 - m[3][2] * s0) * invdet;
    out[3][3] = ( m[2][0] * s3 - m[2][1] * s1 + m[2][2] * s0) * invdet;
  }

  /**
   * @brief Transposes the matrix m and writes result into out
   */
  template <std::size_t R, std::size_t C>
  static void transpose(const T (&m)[R][C], const T (&out)[C][R]) {
    for(int i = 0; i< R; ++i) {
      for(int j = 0; j < C; ++j) {
        out[j][i] = m[i][j];
      }
    }
  }
};

/**
 * @brief Mutiplies two matrices. Just for internal use!
 * 
 * @param lh left matrix
 * @param rh right matrix
 * @param out result is written into this out-parameter 
 * @return [description]
 */
template <typename Ta,
          typename Tb,
          std::size_t Ra,
          std::size_t CR,
          std::size_t Cb>
inline void matrixMultiply(const Ta (&lh)[Ra][CR],
                   const Tb (&rh)[CR][Cb],
                   decltype(Ta(0) * Tb(0)) (&out)[Ra][Cb]) {
  for(int i = 0; i < Ra; ++i) {
    for(int j = 0; j < Cb; ++j) {
      out[i][j] = 0;
      for(int k = 0; k < CR; ++k) {
        out[i][j] += lh[i][k] * rh[k][j];
      }
    }
  }
}

// overload for 2x2
inline void matrixMultiply(const float (&lh)[2][2],
                   const float (&rh)[2][2],
                   float (&out)[2][2]) {
  out[0][0] = lh[0][0]*rh[0][0] + lh[0][1]*rh[1][0];
  out[0][1] = lh[0][0]*rh[0][1] + lh[0][1]*rh[1][1];
  out[1][0] = lh[1][0]*rh[0][0] + lh[1][1]*rh[1][0];
  out[1][1] = lh[1][0]*rh[0][1] + lh[1][1]*rh[1][1];
}

// overload for 3x3
inline void matrixMultiply(const float (&lh)[3][3],
                   const float (&rh)[3][3],
                   float (&out)[3][3]) {
  for(int i = 0; i < 3; ++i) {
    for(int j = 0; j < 3; ++j) {
      out[i][j] = lh[i][0] * rh[0][j] + lh[i][1] * rh[1][j] + lh[i][2]
                                                              * rh[2][j];
    }
  }
}

// overload for 4x4 (uses SSE)
inline void matrixMultiply(const float (&lh)[4][4],
                   const float (&rh)[4][4],
                   float (&out)[4][4]) {
  const __m128 a = _mm_loadu_ps(rh[0]);
  const __m128 b = _mm_loadu_ps(rh[1]);
  const __m128 c = _mm_loadu_ps(rh[2]);
  const __m128 d = _mm_loadu_ps(rh[3]);
  __m128 t1, t2;

  t1 = _mm_set_ps1(lh[0][0]);
  t2 = _mm_mul_ps(a, t1);
  t1 = _mm_set_ps1(lh[0][1]);
  t2 = _mm_add_ps(_mm_mul_ps(b, t1), t2);
  t1 = _mm_set_ps1(lh[0][2]);
  t2 = _mm_add_ps(_mm_mul_ps(c, t1), t2);
  t1 = _mm_set_ps1(lh[0][3]);
  t2 = _mm_add_ps(_mm_mul_ps(d, t1), t2);
  _mm_storeu_ps(out[0], t2);

  t1 = _mm_set_ps1(lh[1][0]);
  t2 = _mm_mul_ps(a, t1);
  t1 = _mm_set_ps1(lh[1][1]);
  t2 = _mm_add_ps(_mm_mul_ps(b, t1), t2);
  t1 = _mm_set_ps1(lh[1][2]);
  t2 = _mm_add_ps(_mm_mul_ps(c, t1), t2);
  t1 = _mm_set_ps1(lh[1][3]);
  t2 = _mm_add_ps(_mm_mul_ps(d, t1), t2);
  _mm_storeu_ps(out[1], t2);

  t1 = _mm_set_ps1(lh[2][0]);
  t2 = _mm_mul_ps(a, t1);
  t1 = _mm_set_ps1(lh[2][1]);
  t2 = _mm_add_ps(_mm_mul_ps(b, t1), t2);
  t1 = _mm_set_ps1(lh[2][2]);
  t2 = _mm_add_ps(_mm_mul_ps(c, t1), t2);
  t1 = _mm_set_ps1(lh[2][3]);
  t2 = _mm_add_ps(_mm_mul_ps(d, t1), t2);
  _mm_storeu_ps(out[2], t2);

  t1 = _mm_set_ps1(lh[3][0]);
  t2 = _mm_mul_ps(a, t1);
  t1 = _mm_set_ps1(lh[3][1]);
  t2 = _mm_add_ps(_mm_mul_ps(b, t1), t2);
  t1 = _mm_set_ps1(lh[3][2]);
  t2 = _mm_add_ps(_mm_mul_ps(c, t1), t2);
  t1 = _mm_set_ps1(lh[3][3]);
  t2 = _mm_add_ps(_mm_mul_ps(d, t1), t2);
  _mm_storeu_ps(out[3], t2);
}


/**
 * @brief Helper class for common Matrix stuff. Just for internal use!
 */
template <typename T, std::size_t R, std::size_t C>
struct MatrixImpl {
  // matrix data
  T data[R][C];

  using type = T;
  static constexpr std::size_t numRows = R;
  static constexpr std::size_t numColumns = C;

  MatrixImpl() {
    setToZero();
  }

  void setToZero() {
    memset(data, 0, sizeof(data));
  }

  Vector<T, C> getRow(std::size_t index) const {
    if(index >= R)
      throw std::out_of_range("Invalid row index");
    Vector<T, C> out;  // TODO: could memcpy for POD types
    for(int i = 0; i < C; ++i) {
      out.data[i] = data[index][i];
    }
    return out;
  }

  Vector<T, R> getColumn(std::size_t index) const {
    if(index >= C)
      throw std::out_of_range("Invalid column index");
    Vector<T, R> out;
    for(int i = 0; i < R; ++i) {
      out.data[i] = data[i][index];
    }
    return out;
  }

  void setRow(std::size_t index, Vector<T, C> vec) {
    if(index >= R)
      throw std::out_of_range("Invalid row index");
    for(int i = 0; i < C; ++i) {
      data[index][i] = vec.data[i];
    }
  }

  void setColumn(std::size_t index, Vector<T, R> vec) {
    if(index >= C)
      throw std::out_of_range("Invalid column index");
    for(int i = 0; i < R; ++i) {
      data[i][index] = vec.data[i];
    }
  }

};

} // namespace internal


/*******************************************************************************
* Definition of Matrix
*******************************************************************************/
/**
 * @brief Represents a RxC matrix with elements of type T
 * 
 * @tparam T Type of elements. Has to be POD!
 * @tparam R Number of Rows
 * @tparam C Number of Columns
 */
template <typename T, std::size_t R, std::size_t C>
struct Matrix : public internal::MatrixImpl<T, R, C> {
  Matrix<T, C, R> transposed() const {
    Matrix<T, C, R> out;
    internal::MatrixHelper<T>::transpose(this->data, out.data);
    return out;
  }
};

// specialization for quadratic matrices
template <typename T, std::size_t N> 
struct Matrix<T, N, N> : public internal::MatrixImpl<T, N, N>{

  Matrix<T, N, N>& setToIdentity() {
    for(int i = 0; i < N; ++i) {
      this->data[i][i] = T(1);
    }
    return *this;
  }

  Vector<T, N> getDiagonal() const {
    Vector<T, N> out;
    for(int i = 0; i < N; ++i) {
      out.data[i] = this->data[i][i];
    }
    return out;
  }

  Matrix<T, N, N>& setDiagonal(Vector<T, N> vec) {
    for(int i = 0; i < N; ++i) {
      this->data[i][i] = vec.data[i];
    }
    return *this;
  }

  T determinant() const {
    return internal::MatrixHelper<T>::det(this->data);
  }

  Matrix<T, N, N> inverted() const {
    Matrix<T, N, N> out;
    internal::MatrixHelper<T>::invert(this->data, out.data);
    return out;
  }

  Matrix<T, N, N> transposed() const {
    Matrix<T, N, N> out;
    internal::MatrixHelper<T>::transpose(this->data, out.data);
    return out;
  }
};



/*******************************************************************************
* Definition of non member functions for Matrix
*******************************************************************************/
/***** unary operators ********************************************************/
template <typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> operator+(const Matrix<T, R, C>& m) {
  return m;
}

template <typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> operator-(const Matrix<T, R, C>& m) {
  // Matrix<T, R, C> out;
  // for(int i = 0; i < R; ++i) {
  //   for(int j = 0; j < C; ++j) {
  //     out.data[i][j] = -m.data[i][j];
  //   }
  // }
  Matrix<T, R, C> out;
  out -= m;
  return out;
}


/***** assignment operators ***************************************************/
// matrix += matrix
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
Matrix<Ta, R, C>& operator+=(Matrix<Ta, R, C>& lh,
                              const Matrix<Tb, R, C>& rh) {
  for(int i = 0; i < R; ++i) {
    for(int j = 0; j < C; ++j) {
      lh.data[i][j] += rh.data[i][j];
    }
  }
  return lh;
}

// matrix -= matrix
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
Matrix<Ta, R, C>& operator-=(Matrix<Ta, R, C>& lh,
                              const Matrix<Tb, R, C>& rh) {
  for(int i = 0; i < R; ++i) {
    for(int j = 0; j < C; ++j) {
      lh.data[i][j] -= rh.data[i][j];
    }
  }
  return lh;
}

// matrix *= matrix
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
Matrix<Ta, R, C>& operator*=(Matrix<Ta, R, C>& lh,
                              const Matrix<Tb, R, C>& rh) {
  matrixMultiply(lh.data, rh.data, lh.data);
  return lh;
}

// matrix *= scalar
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
Matrix<Ta, R, C>& operator*=(Matrix<Ta, R, C>& lh, Tb rh) {
  for(int i = 0; i < R; ++i) {
    for(int j = 0; j < C; ++j) {
      lh.data[i][j] *= rh;
    }
  }
  return lh;
}

// matrix /= scalar
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
Matrix<Ta, R, C>& operator/=(Matrix<Ta, R, C>& lh, Tb rh) {
  for(int i = 0; i < R; ++i) {
    for(int j = 0; j < C; ++j) {
      lh.data[i][j] /= rh;
    }
  }
  return lh;
}


/***** arithmetic operators ***************************************************/
// matrix * scalar
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
auto operator*(const Matrix<Ta, R, C>& lh, Tb rh)
  -> Matrix<decltype(Ta(0) * Tb(0)), R, C> {
  Matrix<decltype(Ta(0) * Tb(0)), R, C> out(lh);
  out *= rh;
  return out;
}

// scalar * matrix
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
auto operator*(Tb lh, const Matrix<Ta, R, C>& rh)
  -> Matrix<decltype(Ta(0) * Tb(0)), R, C> {
  Matrix<decltype(Ta(0) * Tb(0)), R, C> out(rh);
  out *= lh;
  return out;
}

// matrix / scalar
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
auto operator/(const Matrix<Ta, R, C>& lh, Tb rh)
  -> Matrix<decltype(Ta(0) / Tb(0)), R, C> {
  Matrix<decltype(Ta(0) / Tb(0)), R, C> out(lh);
  out /= rh;
  return out;
}

// matrix + matrix
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
auto operator+(const Matrix<Ta, R, C>& lh, const Matrix<Tb, R, C>& rh)
  -> Matrix<decltype(Ta(0) + Tb(0)), R, C> {
  Matrix<decltype(Ta(0) + Tb(0)), R, C> out(lh);
  out += rh;
  return out;
}

// matrix - matrix
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
auto operator-(const Matrix<Ta, R, C>& lh, const Matrix<Tb, R, C>& rh)
  -> Matrix<decltype(Ta(0) - Tb(0)), R, C> {
  Matrix<decltype(Ta(0) - Tb(0)), R, C> out(lh);
  out -= rh;
  return out;
}

// matrix * matrix
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
auto operator*(const Matrix<Ta, R, C>& lh, const Matrix<Tb, R, C>& rh)
  -> Matrix<decltype(Ta(0) * Tb(0)), R, C> {
  Matrix<decltype(Ta(0) * Tb(0)), R, C> out(lh);
  matrixMultiply(lh.data, rh.data, out.data);
  return out;
}

// matrix * vector
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
auto operator*(const Matrix<Ta, R, C>& lh, Vector<Tb, C> rh)
  -> Vector<decltype(Ta(0) + Tb(0)), R> {
  Vector<decltype(Ta(0) + Tb(0)), R> out;
  matrixMultiply(lh.data,
                reinterpret_cast<Tb(&)[C][1]>(rh.data),
                reinterpret_cast<Tb(&)[C][1]>(out.data));
  return out;
}

// vector * matrix
template <typename Ta, typename Tb, std::size_t R, std::size_t C>
auto operator*(Vector<Tb, R> lh, const Matrix<Ta, R, C>& rh)
  -> Vector<decltype(Ta(0) + Tb(0)), C> {
  Vector<decltype(Ta(0) + Tb(0)), C> out;
  matrixMultiply(reinterpret_cast<Tb(&)[1][R]>(lh.data),
                rh.data,
                reinterpret_cast<Tb(&)[1][C]>(out.data));
  return out;
}



/*******************************************************************************
* Definition of matrix_cast
*******************************************************************************/
template <typename Tdst, typename Tsrc>
Tdst matrix_cast(const Tsrc& in) {
  Tdst out;  // init to 0

  // copy avaiable data
  for(int i = 0; i < Tdst::numRows && i < Tsrc::numRows; ++i) {
    for(int j = 0; j < Tdst::numColumns && j < Tsrc::numColumns; ++j) {
      out.data[i][j] = static_cast<typename Tdst::type>(in.data[i][j]);
    }
  }

  // fill diagonal
  for(int i = lxMin(Tsrc::numRows, Tsrc::numColumns);
      i < lxMin(Tdst::numRows, Tdst::numColumns);
      ++i) {
    out.data[i][i] = typename Tdst::type(1);
  }
  return out;
}


/*******************************************************************************
* Typedefs for common types
*******************************************************************************/
template <typename T, std::size_t N>
using MatQ = Matrix<T, N, N>;

template <std::size_t N>
using MatQf = MatQ<float, N>;
template <std::size_t N>
using MatQi = MatQ<int, N>;

using Mat2f = MatQ<float, 2>;
using Mat2i = MatQ<int, 2>;

using Mat3f = MatQ<float, 3>;
using Mat3i = MatQ<int, 3>;

using Mat4f = MatQ<float, 4>;
using Mat4i = MatQ<int, 4>; 

using Mat2x3f = Matrix<float, 2, 3>;
using Mat2x4f = Matrix<float, 2, 4>;
using Mat3x2f = Matrix<float, 3, 2>;
using Mat3x4f = Matrix<float, 3, 4>;
using Mat4x2f = Matrix<float, 4, 2>;
using Mat4x3f = Matrix<float, 4, 3>;

using Mat2x3i = Matrix<int, 2, 3>;
using Mat2x4i = Matrix<int, 2, 4>;
using Mat3x2i = Matrix<int, 3, 2>;
using Mat3x4i = Matrix<int, 3, 4>;
using Mat4x2i = Matrix<int, 4, 2>;
using Mat4x3i = Matrix<int, 4, 3>;



} // namespace lumina