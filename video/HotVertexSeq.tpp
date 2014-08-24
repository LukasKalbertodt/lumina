namespace lumina {

template <typename... Ts>
HotVertexSeq<Ts...>::HotVertexSeq(VertexSeq<Ts...>& ref, void* vbuf, void* ibuf)
  : vertex(ref.m_vertexCount, vbuf),
    index(ref.m_indexCount, ibuf),
    m_cold(ref) {}






// template <typename... Cs>
// void HotVertexSeq<Cs...>::applyVertexLayout() {
//   internal::applyLayoutImpl<0, internal::LayoutTypes<Cs...>::stride,
//                             0, sizeof(Cs)...>();

//   checkGLError("[HotVertexSeq] Error<", GLERR, 
//                "> while applying vertex layout!");
//   m_cold.m_layoutActive = true;
// }

// inline HotVertexSeq<>::HotVertexSeq(VertexSeq& ref)
//   : internal::HotVertexSeqBase(ref),
//     vertex(ref.m_vertexCount, ref.m_vertexSize) {
// }

// template <typename... Cs>
// void HotVertexSeq<>::applyVertexLayout() {
//   internal::applyLayoutImpl<0, internal::LayoutTypes<Cs...>::stride,
//                             0, sizeof(Cs)...>();

//   checkGLError("[HotVertexSeq] Error<", GLERR, 
//                "> while applying vertex layout!");
//   m_cold.m_layoutActive = true;
// }

}  // namespace lumina