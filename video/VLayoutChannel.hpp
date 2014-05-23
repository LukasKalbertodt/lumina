#pragma once

#include "VLayoutChannel.fpp"
#include <bitset>


namespace lumina {

class VLayoutChans {
public:
  VLayoutChans() = default;
  VLayoutChans(VLayoutChannel chan);

  VLayoutChans operator|(VLayoutChannel chan);
  bool operator&(VLayoutChannel chan);

  int count() const;

private:
  std::bitset<32> m_chans;
};

VLayoutChans operator|(VLayoutChannel a, VLayoutChannel b);

}

#include "VLayoutChannel.tpp"