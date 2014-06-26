namespace lumina {

template <typename... Ts> 
void GLObject::checkGLError(Ts... msgs) {
  auto err = glGetError();

  if(err != GL_NO_ERROR) {
    logError(translateErrorMsg(err, msgs)...);
    throw GLException(translateErrorMsg(err, msgs)...);
  }
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