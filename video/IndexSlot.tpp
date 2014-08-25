namespace lumina {

inline IndexSlot::IndexSlot(unsigned int& data) : m_data(data) {}

inline IndexSlot& IndexSlot::operator=(unsigned int v) {
  m_data = v;
  return *this;
}
inline IndexSlot& IndexSlot::operator=(const IndexSlot& copy) {
  m_data = copy.m_data;
  return *this;
}
inline IndexSlot& IndexSlot::operator=(GLIndex) {
  m_data = std::numeric_limits<unsigned int>::max();
  return *this;
}


}