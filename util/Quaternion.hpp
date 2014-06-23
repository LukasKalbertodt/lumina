#pragma once
/**
 * \file Quaternion.hpp
 * This file is part of the Lumina Graphics Framework.
 *
 * \author Julian Kniephoff <julian.kniephoff@gmail.com>
 *
 * This file will define Quaternion.
 */

#include <cmath>

namespace lumina{

/**
 *
 * @brief Represents the hamilton ring H(T) for an arbitrary type T.
 *
 * For certain special values of T, this might alternatively be called the set of quaternions.
 * The quaternion represented is q = w + xi + yj + zk.
 *
 * @tparam T coefficient type. Assumed to be a ring.
 */
template <typename T>
struct Quaternion {
  T w, x, y, z;

  Quaternion(T w, T x, T y, T z)
    : w(w), x(x), y(y), z(z) {
  }

  Quaternion()
    : Quaternion(static_cast<T>(0),
                 static_cast<T>(0),
                 static_cast<T>(0),
                 static_cast<T>(0)) {
  }

  /***** Set operations *********************************************************/
  bool operator==(const Quaternion<T>& other) const {
    return
      this->w == other.w &&
      this->x == other.x &&
      this->y == other.y &&
      this->z == other.z;
  }

  bool operator!=(const Quaternion<T>& other) const {
    return !(*this == other);
  }

  /***** Vector space operations ************************************************/
  Quaternion<T> operator+() const {
    return *this;
  }

  Quaternion<T> operator-() const {
    return Quaternion(-w, -x, -y, -z);
  }

  template <typename OT>
  Quaternion<T>& operator+=(const Quaternion<OT> q) {
    this->w += q.w;
    this->x += q.x;
    this->y += q.y;
    this->z += q.z;

    return *this;
  }

  template <typename OT>
  Quaternion<T>& operator-=(const Quaternion<OT>& q) {
    return *this += -q;
  }

  template <typename S>
  Quaternion<T>& operator*=(S s) {
    this->w *= s;
    this->x *= s;
    this->y *= s;
    this->z *= s;

    return *this;
  }

  template <typename S>
  Quaternion<T>& operator/=(S s) {
    return *this *= 1/s;
  }

  /***** Properties of the Banach space *****************************************/
  T lengthSquared() const {
    return w*w + x*x + y*y + z*z;
  }

  template <typename Tout = decltype(std::sqrt(T(0)))>
  Tout length() const {
    return static_cast<Tout>(std::sqrt(lengthSquared()));
  }

  Quaternion<T>& normalize() {
    auto lensq = lengthSquared();
    if(lensq != 0) {
      *this /= std::sqrt(lensq);
    }
    return *this;
  }

  Quaternion<T> normalized() const {
    return Quaternion<T>(*this).normalize();
  }

  /***** Ring structure *********************************************************/
  template <typename OT>
  Quaternion<T>& operator*=(const Quaternion<OT>& q) {
    return *this = Quaternion<T>(this->w*q.w - this->x*q.x - this->y*q.y - this->z*q.z,
                                 this->w*q.x + this->x*q.w + this->y*q.z - this->z*q.y,
                                 this->w*q.y - this->x*q.z + this->y*q.w + this->z*q.x,
                                 this->w*q.z + this->x*q.y - this->y*q.x + this->z*q.w);
  }

  /***** Division algebra structure *********************************************/
  Quaternion<T>& invert() {
    auto lensq = lengthSquared();
    if(lensq != 0) {
	    (*this).conjugate() /= lensq;
    }
    return *this;
  }

  Quaternion<T> inverse() {
    return Quaternion<T>(*this).invert();
  }

  Quaternion<T>& conjugate() {
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;

    return *this;
  }

  Quaternion<T> conjugated() {
    return Quaternion<T>(*this).conjugate();
  }
};

// =============================================================================
// Definition of non member functions for Vector
// =============================================================================

/***** Vector space operations ************************************************/
template <typename T1, typename T2>
auto operator+(const Quaternion<T1>& q1, const Quaternion<T2>& q2)
    -> Quaternion<decltype(T1(0) + T2(0))> {
  Quaternion<decltype(T1(0) + T2(0))> out(q1);
  return out += q2;
}

template <typename T1, typename T2>
auto operator-(const Quaternion<T1>& q1, const Quaternion<T2>& q2)
    -> Quaternion<decltype(T1(0) - T2(0))> {
  return q1 + (-q2);
}

template <typename T, typename S>
auto operator*(const Quaternion<T>& q, S s)
    -> Quaternion<decltype(T(0) * S(0))> {
  Quaternion<decltype(T(0) * S(0))> out(q);
  return out *= s;
}

template <typename T, typename S>
auto operator*(S s, const Quaternion<T>& q)
    -> Quaternion<decltype(T(0) * S(0))> {
  return q * s;
}

template <typename T, typename S>
auto operator/(const Quaternion<T>& q, S s)
    -> Quaternion<decltype(T(0) / S(0))> {
  return q * (1/s);
}

template <typename T, typename S>
auto operator/(S s, const Quaternion<T>& q)
    -> Quaternion<decltype(T(0) / S(0))> {
  return s * q.inverse();
}

}