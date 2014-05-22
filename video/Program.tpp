namespace lumina {

inline Program::Program() : m_program(0) {}
inline Program::Program(Program& ref) : m_program(ref.m_program) {}


inline HotProgram::HotProgram(Program& ref)
  : Program(ref), uniform(this->m_program) {
  glUseProgram(this->m_program);
}

inline HotProgram::~HotProgram() {
  glUseProgram(0);
  this->m_program = 0;
}

}