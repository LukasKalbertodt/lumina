#pragma once
/**
 * \file TransformationMatrices.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Julian Kniephoff <julian.kniephoff@gmail.com>
 * 
 * This file defines functions to create transformation matrices.
 */

#include "VectorCore.hpp"
#include "Quaternion.hpp"
#include "MatrixCore.hpp"

#include <cmath>

namespace lumina {

// We are mostly dealing with 4x4 matrices here.
template <typename T>
using Mat4 = MatQ<T, 4>;

template <typename T>
Mat4<T> translationMatrix(Vec3<T> translation) {
  Mat4<T> translationMatrix;
  Vec4<T> column = Vec4<T>(translation.x, translation.y, translation.z, static_cast<T>(1));
  translationMatrix.setToIdentity().setColumn(3, column);
  return translationMatrix;
}

template <typename T>
Mat4<T> scalingMatrix(Vec3<T> scaling) {
	Vec4<T> diagonal = Vec4<T>(scaling.x, scaling.y, scaling.z, static_cast<T>(1));
  Mat4<T> scalingMatrix;
  scalingMatrix.setToZero();
  scalingMatrix.setDiagonal(diagonal);
  return scalingMatrix;
}

template <typename T>
Mat4<T> rotationMatrix(Quaternion<T> rotation) {
  Mat4<T> rotationMatrix;
  rotationMatrix.setToIdentity();

  T _2qx2 = 2 * rotation.x * rotation.x;
  T _2qy2 = 2 * rotation.y * rotation.y;
  T _2qz2 = 2 * rotation.z * rotation.z;

  T _2qxqy = 2 * rotation.x * rotation.y;
  T _2qxqz = 2 * rotation.x * rotation.z;
  T _2qxqw = 2 * rotation.x * rotation.w;
  T _2qyqz = 2 * rotation.y * rotation.z;
  T _2qyqw = 2 * rotation.y * rotation.w;
  T _2qzqw = 2 * rotation.z * rotation.w;

  rotationMatrix.data[0][0] -= _2qy2 + _2qz2;
  rotationMatrix.data[0][1] = _2qxqy - _2qzqw;
  rotationMatrix.data[0][2] = _2qxqz + _2qyqw;

  rotationMatrix.data[1][0] = _2qxqy + _2qzqw;
  rotationMatrix.data[1][1] -= _2qx2 + _2qz2;
  rotationMatrix.data[1][2] = _2qyqz - _2qxqw;

  rotationMatrix.data[2][0] = _2qxqz - _2qyqw;
  rotationMatrix.data[2][1] = _2qyqz + _2qxqw;
  rotationMatrix.data[2][2] -= _2qx2 + _2qy2;

  return rotationMatrix;
}

template <typename T>
Mat4<T> viewMatrix(Vec3<T> eye, Vec3<T> direction, Vec3<T> up) {
  Vec3<T> z = -direction.normalized();
  Vec3<T> x = cross(direction, up).normalized();
  Vec3<T> y = cross(z, x);

  Mat4<T> basisChangeMatrix;
  basisChangeMatrix.setToIdentity();
  basisChangeMatrix.setRow(0, Vec4<T>(x.x, x.y, x.z, 0.f));
  basisChangeMatrix.setRow(1, Vec4<T>(y.x, y.y, y.z, 0.f));
  basisChangeMatrix.setRow(2, Vec4<T>(z.x, z.y, z.z, 0.f));

  return translationMatrix(-eye) * basisChangeMatrix;
}

template <typename T>
Mat4<T> projectionMatrix(T fovy, T aspect, T near, T far) {
  Mat4<T> projectionMatrix;
  projectionMatrix.setToZero();
  // cot(x) = tan(pi/2 - x)
  T d = static_cast<T>(std::tan(M_PI_2 - fovy / 2));
  T _1_n_f = 1 / (near - far);

  projectionMatrix.data[0][0] = d / aspect;
  projectionMatrix.data[1][1] = d;
  projectionMatrix.data[2][2] = (near + far) * _1_n_f;
  projectionMatrix.data[2][3] = 2 * near * far * _1_n_f;
  projectionMatrix.data[3][2] = -1;

  return projectionMatrix;
}

}