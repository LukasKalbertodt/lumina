namespace lumina {

inline bool TextureUnits::isPrimed(int index) {
  init();
  return s_primedUnits[index];
}

inline void TextureUnits::setPrimed(int index) {
  init();
  if(!s_primedUnits[index]) {
    s_primedCount++;
  }
  s_primedUnits[index] = true;
}

inline int TextureUnits::countPrimed() {
  return s_primedCount;
}

inline void TextureUnits::unsetPrimed(int index) {
  init();
  if(s_primedUnits[index]) {
    s_primedCount--;
  }
  s_primedUnits[index] = false;
}

inline void TextureUnits::init() {
  static bool ready = false;
  if(!ready) {
    s_primedUnits.resize(getMaxTexUnits());
    ready = true;
  }
}

} // namespace lumina