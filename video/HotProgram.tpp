namespace lumina {

inline HotProgram::HotProgram(Program& ref)
  : uniform(ref.m_handle), m_cold(ref) {
  if(s_isPrimed) {
    logError("Attempt to prime a program while another is already primed!");
    throw GLException(
      "Attempt to prime a program while another is already primed!");
  }
  glUseProgram(m_cold.m_handle);
  s_isPrimed = true;
}

inline HotProgram::~HotProgram() {
  glUseProgram(0);
  s_isPrimed = false;
}


template <typename... Ts>
void HotProgram::draw(const HotVertexSeq<Ts...>& data,
                      PrimitiveType type,
                      int offset,
                      int count) {
  GLenum primitiveType = translatePrimitiveType(type);
  if(data.m_cold.m_indexHandle == 0) {
    glDrawArrays(primitiveType, offset, count);
  }
  else {
    glDrawElements(primitiveType, count, GL_UNSIGNED_INT,
                   reinterpret_cast<void*>(4 * offset));
  }
}


}