namespace lumina {

// =============================================================================
// VertexSlot<T, Ts...>
// =============================================================================
template <typename T, typename... Ts>
VertexSlot<T, Ts...>::VertexSlot(void* buffer) : m_buffer(buffer) {}

template <typename T, typename... Ts>
void VertexSlot<T, Ts...>::set(T head, Ts... tail) {
  *static_cast<T*>(m_buffer) = head;
  VertexSlot<Ts...>(static_cast<T*>(m_buffer) + 1).set(tail...);
}



// =============================================================================
// VertexSlot<T>
// =============================================================================
template <typename T>
VertexSlot<T>::VertexSlot(void* buffer) : m_buffer(buffer) {}

template <typename T> 
void VertexSlot<T>::operator=(T data) {
  *static_cast<T*>(this->m_buffer) = data;
}

template <typename T>
void VertexSlot<T>::set(T head) { 
  *static_cast<T*>(this->m_buffer) = head; 
}

} // namespace lumina