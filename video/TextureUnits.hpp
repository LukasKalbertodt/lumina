#pragma once

#include <vector>

namespace lumina {


class TextureUnits {
public:
  static bool isPrimed(int index);
  static void setPrimed(int index);
  static void unsetPrimed(int index);

private:
  static std::vector<bool> s_primedUnits;
  static void init();
};

int getMaxTexUnits();

}