#pragma once

namespace lumina {

enum class VLayoutChannel {
  Position,
  Normal,
  Tangent,
};

class VLayoutChans {

};

GeometryData operator|(GeometryData a, GeometryData b) {
  return +a | +b;
}

bool operator&(GeometryData a, GeometryData b) {
  return (+a & +b) != 0;
}

int countGeometryChannels(GeometryData d) {
  int out = 0;
  while(d) {

  }
}

}