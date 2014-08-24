namespace lumina {

inline IndexSet::IndexSet(int indexCount, unsigned int* buffer)
  : m_buffer(buffer), m_indexCount(indexCount) {}


inline IndexSlot IndexSet::operator[](int index) {
  if(index >= m_indexCount) {
    logThrowGL("[IndexSet] Index <", index, "> out of bounds!");
  }
  return std::move(IndexSlot(*(m_buffer + index)));
}


} // namespace lumina