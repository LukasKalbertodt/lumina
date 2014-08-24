namespace lumina {

template <typename... Cs>
VertexSet<Cs...>::VertexSet()
  : m_buffer(nullptr), m_slotCount(vertexCount) {}

template <typename... Cs>
VertexSlot<Cs...> VertexSet<Cs...>::operator[](int index) {
  // test if index is valid (in bounds)
  if(index >= m_slotCount) {
    slogAndThrow<GLException>("[VertexSet] Index <", index,
                              "> out of bounds <", m_slotCount, ">!");
  }

  // calculate offset and return another helper object
  auto* buf = static_cast<char*>(m_buffer)  
              + index * internal::VertexLayout<Cs...>::stride;
  return VertexSlot<Cs...>(buf);
}

template <typename... Cs> int VertexSet<Cs...>::size() const {
  return m_slotCount;
}

template <typename... Cs> void* VertexSet<Cs...>::buf() const {
  return m_buffer;
}


} // namespace lumina