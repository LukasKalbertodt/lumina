#pragma once

#include "GLException.hpp"
#include "GLTools.hpp"
#include "Program.fpp"
#include "UniformSlot.hpp"
#include "../config/BaseProxy.hpp"
#include "../util/NonCopyable.hpp"
#include <GL/glew.h>
#include <string>

namespace lumina {
namespace internal {

struct UniformSet : public NonCopyable, public config::CommonBase {
public:
  UniformSlot operator[](std::string at) {
    auto index = glGetUniformLocation(m_program, at.c_str());

    // check for error
    auto err = glGetError();
    if(err != GL_NO_ERROR) {
      logError("[UniformSet] Error while obtaining uniform offset <",
               translateGLError(err),
               ">!");
      throw GLException("[UniformSet] Error while obtaining uniform offset");
    }

    // check if name lookup was successful
    if(index == -1) {
      logWarning("[UniformSet] Uniform with name <", at, "> does not exists!");
    }

    return UniformSlot(index);
  }

private:
  GLuint m_program;

  UniformSet(GLuint prog) : m_program(prog) {}

  friend ::lumina::HotProgram;
};

}
}