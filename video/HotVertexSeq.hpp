#pragma once

#include "GLException.hpp"
#include "GLObject.hpp"
#include "GLTools.hpp"
#include "HotVertexSeq.fpp"
#include "IndexSet.hpp"
#include "VertexSeq.hpp"
#include "HotProgram.fpp"
#include "PrimitiveType.hpp"
#include "VertexSet.hpp"
#include "../config/BaseProxy.hpp"
#include "../util/NotCloneable.hpp"

namespace lumina {
/** Hot version of VertexSeq.
 * A VertexSeq that is currently bound. This enables you to change the data of 
 * the buffers and apply a vertex layout. There is a type-safe and a type-unsafe 
 * variant of HotVertexSeq. You should use the type-safe one whenever you can.
 * When the type-safe variant is used, additional compile-time checks will be
 * performed to reduces bugs.
 * 
 * \tparam Cs The list of types that was given to VertexSeq::prime. It 
 * represents the vertex attributes.
 * 
 * \see VertexSeq
 * \see HotVertexSeq<>
 */
template <typename... Cs>
class HotVertexSeq : public GLObject, private NotCloneable {
public:
  /// The vertex buffer
  VertexSet<Cs...> vertex;

  /// The index buffer
  IndexSet index;


private:
  VertexSeq<Cs...> m_cold;

  // private constructor -> called by VertexSeq
  HotVertexSeq(VertexSeq<Cs...>& ref, void* vbuf, void* ibuf);

  // friend declaration
  friend VertexSeq<Cs...>;
};

// /** The type-unsafe variant of HotVertexSeq.
//  *
//  * \see HotVertexSeq
//  */
// template <>
// class HotVertexSeq<> : public internal::HotVertexSeqBase {
// public:
//   /** Applies the vertex layout.
//    * This method needs to be called to tell OpenGL how a vertex looks like. When
//    * this method isn't called an attempt to draw this VertexSeq will fail.
// 
//    * \tparam Ts The same parameter as the parameters for VertexSeq::prime or
//    * the type-safe variant of HotVertexSeq.
//    */
//   template <typename... Ts>
//   void applyVertexLayout();
// 
//   /// The vertex buffer
//   internal::VertexSet<> vertex;
// 
//   /// The index buffer
//   internal::IndexSet index;
// 
// private:
//   HotVertexSeq(VertexSeq& ref);
// 
//   template <typename...> friend VertexSeq;
// };

} // namespace lumina

#include "HotVertexSeq.tpp"