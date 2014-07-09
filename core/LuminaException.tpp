namespace lumina {

template <typename... Ts> 
LuminaException::LuminaException(Ts... msgs) {
  append(msgs...);
}

inline LuminaException::LuminaException(const LuminaException& copy)
  : m_what(copy.m_what.str()) {}

template <typename T, typename... Ts>
void LuminaException::append(T head, Ts... tail) {
  m_what << head;
  append(tail...);
}

template <typename T>
void LuminaException::append(T last) {
  m_what << last;
}

inline const char* LuminaException::what() const noexcept {
  return m_what.str().c_str();
}


}