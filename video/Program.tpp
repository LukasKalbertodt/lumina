namespace lumina {

inline Program::Program() : m_program(0) {}
inline Program::Program(Program& ref) : m_program(ref.m_program) {}

inline Program::~Program() {
  // 0 will be ignored
  glDeleteProgram(m_program);
}

inline HotProgram::HotProgram(Program& ref)
  : Program(ref), uniform(this->m_program) {
  if(s_isPrimed) {
    logError("Attempt to prime a program while another is already primed!");
    throw GLException(
      "Attempt to prime a program while another is already primed!");
  }
  glUseProgram(this->m_program);
  s_isPrimed = true;
}

inline HotProgram::~HotProgram() {
  glUseProgram(0);
  this->m_program = 0;
  s_isPrimed = false;
}

inline void Program::prime(std::function<void(HotProgram&)> func) {
  if(m_program == 0) {
    logError("[Program] Attempt to prime program before it was created!");
    throw GLException(
      "[Program] Attempt to prime program before it was created!");
  }
  HotProgram hot(*this);
  func(hot);
}

}