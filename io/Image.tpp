#pragma once

namespace lumina {

template <typename C>
void Image<C>::create(Vec2i size) {
  m_size = size;
  m_data.reset(new C[size.linearSize()]);
}

template <typename C>
C& Image<C>::pixelAt(Vec2i pos) {
  if(!m_data) {
    logError("[Image] Called 'pixelAt' on not created image!");
    throw NotReadyEx("[Image] Called 'pixelAt' on not created image");
  }

  if(pos.x >= m_size.x || pos.y >= m_size.y) {
    logError("[Image] Pixel out of bounds: Requested <", pos, 
      "> on image size <", m_size, ">!");
    throw LuminaException("[Image] Pixel out of bounds");
  }

  return m_data[pos.y*m_size.x + pos.x];
}

} // namespace lumina


