#pragma once

#include "Program.fpp"
#include "UniformSet.fpp"
#include "../config/BaseProxy.hpp"
#include "../util/MatrixCore.hpp"
#include "../util/VectorCore.hpp"

namespace lumina { 
namespace internal {

struct UniformSlot : public config::CommonBase {
public:

  void operator=(float);
  void operator=(int);
  void operator=(unsigned int);

  void operator=(Vec2f);
  void operator=(Vec3f);
  void operator=(Vec4f);

  void operator=(Vec2i);
  void operator=(Vec3i);
  void operator=(Vec4i);

  void operator=(Mat4f);
  void operator=(Mat3f);
  void operator=(Mat2f);

  void operator=(Mat2x3f);
  void operator=(Mat2x4f);
  void operator=(Mat3x2f);
  void operator=(Mat3x4f);
  void operator=(Mat4x2f);
  void operator=(Mat4x3f);

private:
  GLuint index;

  UniformSlot(GLuint index) : index(index) {}

  friend UniformSet;
};

}
}