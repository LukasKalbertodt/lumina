#pragma once

namespace lumina {

template <typename C>
void Image<C>::create(Vec2i size) {
  m_size = size;
  m_data.reset(new C[size.linearSize()]);
}

template <typename C>
C& Image<C>::operator[](Vec2i pos) {
  if(!m_data) {
    logError("[Image] Called 'operator[]' on not created image!");
    throw NotReadyEx("[Image] Called 'operator[]' on not created image");
  }

  if(config::debugBoundChecks) {
    if(pos.x >= m_size.x || pos.y >= m_size.y) {
      logError("[Image] Pixel out of bounds: Requested <", pos, 
        "> on image size <", m_size, ">!");
      throw LuminaException("[Image] Pixel out of bounds");
    }
  }

  return m_data[pos.y*m_size.x + pos.x];
}

template <typename C>
C* Image<C>::data() {
  return m_data.get();
}

} // namespace lumina


