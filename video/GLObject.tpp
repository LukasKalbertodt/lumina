namespace lumina {

template <typename... Ts> 
void GLObject::checkGLError(Ts... msgs) {
  auto err = glGetError();

  if(err != GL_NO_ERROR) {
    logAndThrow<GLException>(translateErrorMsg(err, msgs)...);
  }
}

template <typename... Ts> 
void GLObject::checkGLWarning(Ts... msgs) {
  auto err = glGetError();

  if(err != GL_NO_ERROR) {
    logWarning(translateErrorMsg(err, msgs)...);
  }
}

template <typename... Ts> void logThrowGL(Ts... msgs) {
  logAndThrow<GLException>(msgs...);
}


template <typename T> 
T& GLObject::translateErrorMsg(GLuint err, T& obj) {
  return obj;
}

inline const char* GLObject::translateErrorMsg(GLuint err, PrintGL print) {
  switch(print) {
    case PrintGL::Error:
      return translateGLError(err);
    default:
      return "???";
  }
}


}