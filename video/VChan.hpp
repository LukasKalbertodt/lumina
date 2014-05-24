#pragma once

#include "VChan.fpp"
#include "../util/Vector.hpp"
#include <bitset>


namespace lumina {

enum class VChan {
  Position,
  Normal,
  Tangent,
  TexUV
};

class VLayoutChans {
public:
  VLayoutChans() = default;
  VLayoutChans(VChan chan);

  VLayoutChans operator|(VChan chan);
  bool operator&(VChan chan);

  int count() const;

private:
  std::bitset<32> m_chans;
};

VLayoutChans operator|(VChan a, VChan b);

namespace internal {

template <VChan C>
struct VChanHelper;

#define X(CHAN_, TYPE_)                                                        \
  template <> struct VChanHelper<VChan::CHAN_> { using type = TYPE_; };

X(Position, Vec3f)
X(Normal, Vec3f)
X(Tangent, Vec3f)
X(TexUV, Vec2f)

#undef X

template <VChan H, VChan... Cs> struct VChansHelper {
  static constexpr int size = sizeof(typename VChanHelper<H>::type) / 4
                              + VChansHelper<Cs...>::size;
};

template <VChan C> struct VChansHelper<C> {
  static constexpr int size = sizeof(typename VChanHelper<C>::type) / 4;
};


} // namespace internal
} // namespace lumina

#include "VChan.tpp"