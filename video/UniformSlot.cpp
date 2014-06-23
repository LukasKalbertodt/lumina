#include "GLException.hpp"
#include "GLTools.hpp"
#include "UniformSlot.hpp"

#include <GL/glew.h>

namespace lumina {
namespace internal {


#define ERROR_CHECK(uniform_name_)                                             \
  auto err = glGetError();                                                     \
  if(err != GL_NO_ERROR) {                                                     \
    logError("[UniformSlot] Error while writing " #uniform_name_ " uniform <", \
             translateGLError(err),                                            \
             ">!");                                                            \
    throw GLException("[UniformSlot] Error while writing " #uniform_name_      \
                      " uniform");                                             \
  }


// =============================================================================
// Define overloads for scalar types
// =============================================================================
#define X(type_, func_)                                                        \
  void UniformSlot::operator=(type_ val) {                                     \
    func_(index, val);                                                         \
    ERROR_CHECK(type_)                                                         \
  }


X(float, glUniform1f)
X(int, glUniform1i)
X(unsigned int, glUniform1ui)

#undef X

// =============================================================================
// Define overloads for vector types
// =============================================================================
#define X(type_, func_, ...)                                                   \
  void UniformSlot::operator=(type_ val) {                                     \
    func_(index, __VA_ARGS__);                                                 \
    ERROR_CHECK(type_);                                                        \
  }


X(Vec2f, glUniform2f, val.x, val.y)
X(Vec3f, glUniform3f, val.x, val.y, val.z)
X(Vec4f, glUniform4f, val.x, val.y, val.z, val.w)

X(Vec2i, glUniform2i, val.x, val.y)
X(Vec3i, glUniform3i, val.x, val.y, val.z)
X(Vec4i, glUniform4i, val.x, val.y, val.z, val.w)

#undef X

// =============================================================================
// Define overloads for matrix types
// =============================================================================
// macro for setting matrix types
#define X(type_, func_)                                                        \
  void UniformSlot::operator=(type_ val) {                                     \
    func_(index, 1, true, &val.data[0][0]);                                    \
    ERROR_CHECK(type_)                                                         \
  }

// quadratic matrices
X(Mat4f, glUniformMatrix4fv)
X(Mat3f, glUniformMatrix3fv)
X(Mat2f, glUniformMatrix2fv)

// other matrices
X(Mat2x3f, glUniformMatrix3x2fv)
X(Mat2x4f, glUniformMatrix4x2fv)
X(Mat3x2f, glUniformMatrix2x3fv)
X(Mat3x4f, glUniformMatrix4x3fv)
X(Mat4x2f, glUniformMatrix2x4fv)
X(Mat4x3f, glUniformMatrix3x4fv)


// undef macro
#undef X

#undef ERROR_CHECK


// template <typename T, std::size_t N>
// void UniformSlot::operator=(Vector<T, N> val) {

// }



} // namespace internal
} // namespace lumina
