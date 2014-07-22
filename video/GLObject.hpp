#pragma once

#include "GLTools.hpp"
#include "GLException.hpp"
#include "../config/BaseProxy.hpp"
#include "../config/LConfig.hpp"
#include "../util/NotCloneable.hpp"

#include <GL/glew.h>
#include <sstream>

namespace lumina {

enum class PrintGL {
  Error
};

class GLContextFreeObject : public config::CommonBase, public NotCopyable {
public:
  // OpenGL object cannot be copied, just moved.
  GLContextFreeObject() = default;

protected:
  template <typename... Ts> void checkGLError(Ts...);
  template <typename... Ts> void checkGLWarning(Ts...);
  template <typename... Ts> void logThrowGL(Ts...);

  // short name for PrintGL::Error
  static constexpr PrintGL GLERR = PrintGL::Error;

private:
  template <typename T> T& translateErrorMsg(GLuint err, T& obj);
  const char* translateErrorMsg(GLuint err, PrintGL obj);

};

class GLObject : public GLContextFreeObject {
public:
  GLObject();

private:
  bool isRenderContextCurrent();
};


}

#include "GLObject.tpp"