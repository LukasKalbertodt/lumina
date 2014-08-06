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

public:
  HotVertexSeqBase(VertexSeq& ref);
  
  // custom destructor
  ~HotVertexSeqBase();

  VertexSeq& m_cold;
  internal::IndexSet index;
};

}

/**
 * @brief Hot version of VertexSeq
 * @details [long description]
 * 
 * @tparam Cs [description]
 */
template <typename... Cs>
class HotVertexSeq : public internal::HotVertexSeqBase {
private:
  HotVertexSeq(VertexSeq& ref);

  friend VertexSeq;

public:
  void applyVertexLayout();

  internal::VertexSet<Cs...> vertex;
};

template <>
class HotVertexSeq<> : public internal::HotVertexSeqBase {
private:
  HotVertexSeq(VertexSeq& ref);

  friend VertexSeq;

public:
  template <typename... Ts>
  void applyVertexLayout();

  internal::VertexSet<> vertex;
};

} // namespace lumina

#include "HotVertexSeq.tpp"