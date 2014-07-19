namespace lumina {

inline HotProgram::HotProgram(Program& ref)
  : uniform(ref.m_handle), m_cold(ref) {
  if(s_isPrimed) {
    logThrowGL("Attempt to prime a program while another is already primed!");
  }
  glUseProgram(m_cold.m_handle);
  s_isPrimed = true;
}

inline HotProgram::~HotProgram() {
  glUseProgram(0);
  s_isPrimed = false;
}

}