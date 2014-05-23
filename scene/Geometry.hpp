#pragma once

#include "../video/Mesh.hpp"
#include "../video/VLayoutChannel.hpp"
#include "../util/Vector.hpp"

namespace lumina {

Mesh createCube(Vec3f size, VLayoutChans data) {
  Mesh out;

  // 8 vertex-points with the number of given channels
  int count = data.count() * 8;
  Mesh.create(count);

  return out;
}

}