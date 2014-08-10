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

namespace internal {

class HotVertexSeqBase : public GLObject, public NotCloneable {
private:
  friend VertexSeq;

protected:
  VertexSeq& m_cold;
  
public:
  HotVertexSeqBase(VertexSeq& ref);
  
  // custom destructor
  ~HotVertexSeqBase();


  /// The index buffer
  internal::IndexSet index;
};

}

/** Hot version of VertexSeq.
A VertexSeq that is currently bound. This enables you to change the data of 
the buffers and apply a vertex layout. There is a type-safe and a type-unsafe 
variant of HotVertexSeq. You should use the type-safe one whenever you can.
When the type-safe variant is used, additional compile-time checks will be
performed to reduces bugs.

\tparam Cs The list of types that was given to VertexSeq::prime. It represents
the vertex attributes.

\see VertexSeq
\see HotVertexSeq<>
*/
template <typename... Cs>
class HotVertexSeq : public internal::HotVertexSeqBase {
private:
  HotVertexSeq(VertexSeq& ref);

  friend VertexSeq;

  void applyVertexLayout();
public:

  /// The vertex buffer
  internal::VertexSet<Cs...> vertex;
};

/** The type-unsafe variant of HotVertexSeq.

\see HotVertexSeq
*/
template <>
class HotVertexSeq<> : public internal::HotVertexSeqBase {
private:
  HotVertexSeq(VertexSeq& ref);

  friend VertexSeq;

public:
  /** Applies the vertex layout.
  This method needs to be called to tell OpenGL how a vertex looks like. When
  this method isn't called an attempt to draw this VertexSeq will fail.

  \tparam Ts The same parameter as the parameters for VertexSeq::prime or
  the type-safe variant of HotVertexSeq.
  */
  template <typename... Ts>
  void applyVertexLayout();

  /// The vertex buffer
  internal::VertexSet<> vertex;
};

} // namespace lumina

#include "HotVertexSeq.tpp"