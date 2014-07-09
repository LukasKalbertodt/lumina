namespace lumina {

inline Program::Program() : m_handle(0) {}
inline Program::Program(Program& ref) : m_handle(ref.m_handle) {}

inline Program::~Program() {
  // 0 will be ignored
  glDeleteProgram(m_handle);
}

}