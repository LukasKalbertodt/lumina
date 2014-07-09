#pragma once

#include "GLException.hpp"
#include "GLObject.hpp"
#include "GLTools.hpp"
#include "HotVertexSeq.fpp"
#include "IndexSet.hpp"
#include "VertexSeq.hpp"
#include "PrimitiveType.hpp"
#include "VertexSet.hpp"
#include "../config/BaseProxy.hpp"


namespace lumina {

/**
 * @brief Hot version of VertexSeq
 * @details [long description]
 * 
 * @tparam Cs [description]
 */
template <typename... Cs>
class HotVertexSeq : public GLObject {
private:
  VertexSeq& m_cold;

  HotVertexSeq(VertexSeq& ref);

  friend VertexSeq;


public:
  // delete copy and move constructors to avoid copys
  HotVertexSeq(const HotVertexSeq&) = delete;
  HotVertexSeq& operator=(const HotVertexSeq&) = delete;
  HotVertexSeq(HotVertexSeq&&) = delete;
  HotVertexSeq& operator==(HotVertexSeq&&) = delete;

  // custom destructor
  ~HotVertexSeq();

  void setPrimitiveType(PrimitiveType type);
  void applyVertexLayout();

  internal::VertexSet<Cs...> vertex;
  internal::IndexSet index;
};

} // namespace lumina

#include "HotVertexSeq.tpp"