#pragma once

#include "VertexAttribute.fpp"
#include "../util/VectorCore.hpp"
#include <bitset>


namespace lumina {

enum class VAttr {
  Position,
  Normal,
  Tangent,
  TexUV
};

class VLayoutChans {
public:
  VLayoutChans() = default;
  VLayoutChans(VAttr chan);

  VLayoutChans operator|(VAttr chan);
  bool operator&(VAttr chan);

  int count() const;

private:
  std::bitset<32> m_chans;
};

VLayoutChans operator|(VAttr a, VAttr b);

namespace internal {

template <VAttr C>
struct VAttrHelper;

#define X(CHAN_, TYPE_)                                                        \
  template <> struct VAttrHelper<VAttr::CHAN_> { using type = TYPE_; };

X(Position, Vec3f)
X(Normal, Vec3f)
X(Tangent, Vec3f)
X(TexUV, Vec2f)

#undef X

template <VAttr H, VAttr... Cs> struct VAttrsHelper {
  static constexpr int size = sizeof(typename VAttrHelper<H>::type) / 4
                              + VAttrsHelper<Cs...>::size;

  template <VAttr S>
  static constexpr bool contains() {
    return ((H == S) || VAttrsHelper<Cs...>::contains());
  }
};

template <VAttr C> struct VAttrsHelper<C> {
  static constexpr int size = sizeof(typename VAttrHelper<C>::type) / 4;

  template <VAttr S> static constexpr bool contains() {
    return (C == S);
  }
};


} // namespace internal
} // namespace lumina

#include "VertexAttribute.tpp"