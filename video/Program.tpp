namespace lumina {

inline Program::Program() : m_handle(0) {}

inline Program::~Program() {
  // 0 will be ignored
  glDeleteProgram(m_handle);
}

}