namespace lumina {

inline GLObject::GLObject() {
  // if(config::debugContextCurrentCheck) {
  //   if(!isRenderContextCurrent()) {
  //     logThrowGL("[GLObject] Trying to create a GLObject, but no render "
  //                "context is current!");
  //   }
  // }
}

template <typename... Ts> 
void GLContextFreeObject::checkGLError(Ts... msgs) {
  auto err = glGetError();

  if(err != GL_NO_ERROR) {
    logAndThrow<GLException>(translateErrorMsg(err, msgs)...);
  }
}

template <typename... Ts>
void GLContextFreeObject::checkGLWarning(Ts... msgs) {
  auto err = glGetError();

  if(err != GL_NO_ERROR) {
    logWarning(translateErrorMsg(err, msgs)...);
  }
}

template <typename... Ts> void GLContextFreeObject::logThrowGL(Ts... msgs) {
  logAndThrow<GLException>(msgs...);
}


template <typename T> 
T& GLContextFreeObject::translateErrorMsg(GLuint err, T& obj) {
  return obj;
}

inline const char* GLContextFreeObject::translateErrorMsg(GLuint err, PrintGL print) {
  switch(print) {
    case PrintGL::Error:
      return translateGLError(err);
    default:
      return "???";
  }
}


}