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
void* Image<C>::data() {
  return m_data.get();
}
template <typename C>
Vec2i Image<C>::dimension() {
  return m_size;
}

template <typename C>
ImageBox::ImageBox(Image<C>&& image) : m_img(new Image<C>(image)) {}


void* ImageBox::data() { return m_img->data(); }
Vec2i ImageBox::dimension() { return m_img->dimension(); }

template <typename C>
Color<C>& ImageBox::get() {
  return dynamic_cast<Color<C>&>(*m_img);
}


} // namespace lumina


