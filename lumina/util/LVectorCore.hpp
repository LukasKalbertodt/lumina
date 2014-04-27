#pragma once
/**
 * \file LVectorCore.hpp
 * This file is part of the Lumina Graphics Framework.
 *
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 *
 * This file will define LVector and various vector functions. In most cases you
 * should include LVector.hpp instead, which provides additional helper
 * functions (but has more dependencies).
 */
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

namespace lumina {

/*******************************************************************************
* Internal Helper: The following is for internal use only!
*******************************************************************************/
/**
 * @brief Specialized helper base struct for LVector.
 *        Just for internal use!
 * 
 * @tparam T Type of the vector data
 * @tparam N Dimension of the vector
 */
template <typename T, std::size_t N>
struct LXVectorImpl {
  static_assert(N > 1, "Are you fucking kidding me?");

  union {
    T data[N];
    struct {
      T x;
      T y;
      T z;
      T w;
    };
  };

  template <typename... Ts>
  LXVectorImpl(Ts... vals)
    : data{static_cast<T>(vals)...} {
    static_assert(sizeof...(Ts) == N, "Number of constructor arguments do not "
      "match the template parameter N!");
  }

  LXVectorImpl()
    : data{static_cast<T>(0)} {
  }
};

// specialization for 2d
template <typename T>
struct LXVectorImpl<T, 2> {
  union {
    T data[2];
    struct {
      T x;
      T y;
    };
  };

  LXVectorImpl(T x, T y)
    : x(x), y(y) {  
  }

  LXVectorImpl()
    : x(static_cast<T>(0)),
      y(static_cast<T>(0)) {
  }

};

// specialization for 3d
template <typename T>
struct LXVectorImpl<T, 3> {
  union {
    T data[3];
    struct {
      T x;
      T y;
      T z;
    };
  };

  LXVectorImpl(T x, T y, T z)
    : x(x), y(y), z(z) {  
  }

  LXVectorImpl()
    : x(static_cast<T>(0)),
      y(static_cast<T>(0)),
      z(static_cast<T>(0)) {
  }
};

// specialization for 4d
template <typename T>
struct LXVectorImpl<T, 4> {
  union {
    T data[4];
    struct {
      T x;
      T y;
      T z;
      T w;
    };
  };

  LXVectorImpl(T x, T y, T z, T w)
    : x(x), y(y), z(z), w(w) {  
  }

  LXVectorImpl()
    : x(static_cast<T>(0)),
      y(static_cast<T>(0)),
      z(static_cast<T>(0)),
      w(static_cast<T>(0)) {
  }
};


/**
 * @brief Calculates the smaller number at compile time.
 *        Just for internal use!
 * 
 * @param a one number
 * @param b another number
 * 
 * @return the smallest of a and b
 */
constexpr std::size_t lxMin(std::size_t a, std::size_t b) {
  return (a > b) ? b : a;
}

/// definition of PI
constexpr double lxVecPI = 3.14159265359;

// forward declare LVectorIterator
template <typename T, std::size_t N>
class LVectorIterator;



/*******************************************************************************
* Definition of LVector
*******************************************************************************/
/**
 * @brief Represents a vector with arbitrary dimension and type of elements.
 * 
 * @tparam T Type of the elements of the vector
 * @tparam N Dimension of the vector
 */
template <typename T, std::size_t N>
struct LVector : public LXVectorImpl<T, N> {

  /***** Constructors, typedefs, data access, conversion **********************/
  /// inheriting constructor from base class
  using LXVectorImpl<T, N>::LXVectorImpl;

  /// iterator type
  using iterator = LVectorIterator<T, N>;
  /// type of the vector's elements
  using type = T;
  /// dimension of the vector
  static constexpr std::size_t size = N; 

  /// subscript operator, throws on invalid subscript
  T& operator[] (std::size_t index) {
    if(index >= N) {
      throw std::out_of_range("Invalid subscript");
    }
    return this->data[index];
  }

  T operator[] (std::size_t index) const {
    if(index >= N) {
      throw std::out_of_range("Invalid subscript");
    }
    return this->data[index];
  }


  /***** simple arithmetic operators, altering the object *********************/
  template <typename OT>
  LVector<T, N>& operator+=(const LVector<OT, N>& v) {
    for(int i = 0; i < N; ++i) {
      this->data[i] += v.data[i];
    }
    return *this;   
  }

  template <typename OT>
  LVector<T, N>& operator-=(const LVector<OT, N>& v) {
    for(int i = 0; i < N; ++i) {
      this->data[i] -= v.data[i];
    }
    return *this;   
  }

  template <typename S>
  LVector<T, N>& operator*=(S scalar) {
    for(int i = 0; i < N; ++i) {
      this->data[i] *= scalar;
    }
    return *this;   
  }

  template <typename S>
  LVector<T, N>& operator/=(S scalar) {
    for(int i = 0; i < N; ++i) {
      this->data[i] /= scalar;
    }
    return *this;   
  }


  /***** Unary operators ******************************************************/
  LVector<T, N> operator+() const {
    return *this;
  }

  LVector<T, N> operator-() const {
    LVector<T, N> out(*this);
    for(int i = 0; i < N; ++i) {
      out.data[i] = -out.data[i];
    }
    return out;
  }


  /***** comparison operators *************************************************/
  bool operator==(const LVector<T, N>& other) const {
    for(int i = 0; i < N; ++i) {
      if(this->data[i] != other.data[i])
        return false;
    }
    return true;
  }

  bool operator!=(const LVector<T, N>& other) const {
    return !(*this == other);
  }

  // TODO: does this make sense?
  bool operator<(const LVector<T, N>& other) const {
    for(int i = 0; i < N; ++i) {
      if(this->data[i] < other.data[i]) 
        return true;
      if(this->data[i] > other.data[i])
        return false;
    }
    return false;
  }

  bool operator>(const LVector<T, N>& other) const {
    return (other < *this);
  }

  bool operator<=(const LVector<T, N>& other) const {
    return (*this < other || *this == other);
  }

  bool operator>=(const LVector<T, N>& other) const {
    return (other < *this || *this == other);
  }


  /***** Arithmetic functions with sclar output *******************************/
  T lengthSquared() const {
    T out = 0;
    for(int i = 0; i < N; ++i) {
      out +=  this->data[i] * this->data[i];
    }
    return out;
  }

  template <typename Tout = decltype(sqrt(T(0)))>
  Tout length() const {
    return static_cast<Tout>(sqrt(lengthSquared()));
  }

  auto phi() const -> decltype(atan2(T(0), T(0))) {
    static_assert(N >= 2, "You cannot calculate phi of a vector which "
      "dimension is lower than 2!");
    auto phi = atan2(this->data[1], this->data[0]);
    return (phi < 0) ? (phi + 2*lxVecPI) : phi;
  }

  auto theta() const -> decltype(acos(T(0))) {
    static_assert(N >= 3, "You cannot calculate theta of a vector which "
      "dimension is lower than 3!");
    return acos(this->data[2] / length());
  }

  T linearSize() const {
    T out = this->data[0];
    for(int i = 1; i < N; ++i) {
      out *= this->data[i];
    }
    return out;
  }


  /***** Arithmetic functions with vector output ******************************/
  LVector<T, N> normalized() const {
    return LVector<T, N>(*this).normalize();
  }

  void normalize() {
    auto lensq = lengthSquared();
    if(lensq != 0) 
      (*this) /= sqrt(lensq);
  }

  template <typename To>
  void scale(const LVector<To, N>& o) {
    for(int i = 0; i < N; ++i) {
      this->data[i] *= o.data[i];
    }
  }

  template <typename To>
  LVector<T, N> scaled(const LVector<To, N>& o) {
    return LVector<T, N>(*this).scale();
  }

  template <typename Ta>
  void rotate(Ta phi, Ta theta) {
    *this = rotated(phi, theta);
  }

  template <typename Ta>
  LVector<T, N> rotated(Ta phi, Ta theta) const {
    return LVector<T, N>(
      cos(theta) * cos(phi) * this->x
        - cos(theta) * sin(phi) * this->y
        + sin(theta) * this->z,
      sin(phi) * this->x
        + cos(phi) * this->y,
      -sin(theta) * cos(phi) * this->x
        + sin(theta) * sin(phi) * this->y
        + cos(theta) * this->z
      );
  }

  template <typename To>
  void reflect(const LVector<To, N>& normal) {
    *this -= normal * 2 * dot(*this, normal);
  }

  template <typename To>
  auto reflected(const LVector<To, N>& normal)
      const -> LVector<decltype(T(0) - To(0)), N> {
    return LVector<decltype(T(0) - To(0)), N>(*this).reflect(normal);
  }
};



/*******************************************************************************
* Definition of non member functions for LVector
*******************************************************************************/
/***** Simple arithmetic operators ********************************************/
template <typename T1, typename T2, std::size_t N>
auto operator+(const LVector<T1, N>& v1, const LVector<T2, N>& v2)
    -> LVector<decltype(T1(0) + T2(0)), N> {
  LVector<decltype(T1(0) + T2(0)), N> out(v1);
  return (out += v2);
}

template <typename T1, typename T2, std::size_t N>
auto operator-(const LVector<T1, N>& v1, const LVector<T2, N>& v2)
    -> LVector<decltype(T1(0) - T2(0)), N> {
  LVector<decltype(T1(0) - T2(0)), N> out(v1);
  return (out -= v2);
}

template <typename T1, typename T2, std::size_t N>
auto operator*(const LVector<T1, N>& v, T2 scalar)
    -> LVector<decltype(T1(0) * T2(0)), N> {
  LVector<decltype(T1(0) * T2(0)), N> out(v);
  return out *= scalar;
}

template <typename T1, typename T2, std::size_t N>
auto operator*(T2 scalar, const LVector<T1, N>& v)
    -> LVector<decltype(T1(0) * T2(0)), N> {
  LVector<decltype(T1(0) * T2(0)), N> out(v);
  return out *= scalar;
}

template <typename T1, typename T2, std::size_t N>
auto operator/(const LVector<T1, N>& v, T2 scalar)
    -> LVector<decltype(T1(0) / T2(0)), N> {
  LVector<decltype(T1(0) / T2(0)), N> out(v);
  return out *= scalar;
}

template <typename T1, typename T2, std::size_t N>
auto operator/(T2 scalar, const LVector<T1, N>& v)
    -> LVector<decltype(T1(0) / T2(0)), N> {
  LVector<decltype(T1(0) / T2(0)), N> out(v);
  return out *= scalar;
}


/***** commutative vector calculations ****************************************/
template <typename T1, typename T2, std::size_t N>
auto dot(const LVector<T1, N>& lh, const LVector<T2, N>& rh)
    -> decltype(T1(0) + T2(0)) {
  decltype(T1(0) + T2(0)) out = 0;
  for(int i = 0; i < N; ++i) {
    out += lh.data[i] * rh.data[i];
  }
  return out;
}

template <typename T1, typename T2>
auto cross(const LVector<T1, 3>& lh, const LVector<T2, 3>& rh)
    -> LVector<decltype(T1(0) * T2(0)), 3> {
  return LVector<decltype(T1(0) + T2(0)), 3>(lh.y * rh.z - lh.z * rh.y,
                                             lh.z * rh.x - lh.x * rh.z,
                                             lh.x * rh.y - lh.y * rh.x);
}


template <typename T1, typename T2, std::size_t N>
auto distance(const LVector<T1, N>& a, const LVector<T2, N>& b)
    -> decltype((a - b).length()) {
  return (a - b).length();
}

template <typename T1, typename T2, std::size_t N>
auto angle(const LVector<T1, N>& a, const LVector<T2, N>& b)
    -> decltype(acos(a.length() * b.length())) {
  return acos(dot(a, b) / (a.length() * b.length()));
}


/***** vector_cast definition *************************************************/
template <typename Tdst, typename Tsrc, std::size_t N>
LVector<Tdst, N> vector_cast(const LVector<Tsrc, N>& in) {
  LVector<Tdst, N> out;
  for(int i = 0; i < N; ++i) {
    out.data[i] = static_cast<Tdst>(in.data[i]);
  }
  return out;
}

template <std::size_t Ndst, std::size_t Nsrc, typename T>
LVector<T, Ndst> vector_cast(const LVector<T, Nsrc>& in) {
  LVector<T, Ndst> out;
  for(int i = 0; i < lxMin(Ndst, Nsrc); ++i) {
    out.data[i] = in.data[i];
  }
  return out;
}

template <typename Tdst, std::size_t Ndst, typename Tsrc, std::size_t Nsrc>
LVector<Tdst, Ndst> vector_cast(const LVector<Tsrc, Nsrc>& in) {
  LVector<Tdst, Ndst> out;
  for(int i = 0; i < lxMin(Ndst, Nsrc); ++i) {
    out.data[i] = static_cast<Tdst>(in.data[i]);
  }
  return out;
}



/*******************************************************************************
* Typedefs for common types
*******************************************************************************/
template <typename T>
using Vec2 = LVector<T, 2>;
using Vec2f = LVector<float, 2>; 
using Vec2i = LVector<int, 2>; 

template <typename T>
using Vec3 = LVector<T, 3>;
using Vec3f = LVector<float, 3>; 
using Vec3i = LVector<int, 3>; 

template <typename T>
using Vec4 = LVector<T, 4>;
using Vec4f = LVector<float, 4>; 
using Vec4i = LVector<int, 4>; 



/*******************************************************************************
* LVectorIterator definition and functions
*******************************************************************************/
template <typename T, std::size_t N>
class LVectorIterator : public LVector<T, N> {
private:
  // LVector<T, N> m_current;
  LVector<T, N> m_target;

  template <typename Tf, std::size_t Nf>
  friend typename LVector<Tf, Nf>::iterator begin(LVector<Tf, Nf> v);
  template <typename Tf, std::size_t Nf>
  friend typename LVector<Tf, Nf>::iterator end(LVector<Tf, Nf> v);

  using iterator = void;

  LVectorIterator(LVector<T, N> v) : m_target(v) {}

  void skipToEnd() {
    this->data[0] = m_target.data[0];
  }

public:
  T operator*() const {
    T out = 0;
    for(int i = 0; i < N; ++i) {
      T add = this->data[i];
      for(int j = i + 1; j < N; ++j) {
        add *= m_target.data[j];
      }
      out += add;
    }
    return out;
  }

  LVectorIterator& operator++() {
    for(int i = N - 1; i > 0; --i) {
      if(++this->data[i] < m_target.data[i])
        return *this;

      this->data[i] = 0;
    }
    ++this->data[0];
    return *this;
  }

  LVectorIterator<T, N> operator++(int) {
    LVectorIterator<T, N> pre(*this);
    ++(*this);
    return pre;
  }
};

template <typename T, std::size_t N>
typename LVector<T, N>::iterator begin(LVector<T, N> v) {
  static_assert(!std::is_floating_point<T>::value, 
    "You cannot obtain a iterator of an floating pointer vector type!");
  return typename LVector<T, N>::iterator(v);
}

template <typename T, std::size_t N>
typename LVector<T, N>::iterator end(LVector<T, N> v) {
  static_assert(!std::is_floating_point<T>::value, 
    "You cannot obtain a iterator of an floating pointer vector type!");
  typename LVector<T, N>::iterator out(v);
  out.skipToEnd();
  return out;
}



};