#pragma once

#include "../config/BaseProxy.hpp"
#include "../config/LConfig.hpp"
#include "../core/LuminaException.hpp"
#include "../util/Color.hpp"
#include "../util/Vector.hpp"

#include <memory>

namespace lumina {

namespace internal {

class ImageBase {

public:
  virtual void* data() = 0;
  virtual Vec2i dimension() = 0;

};

}


template <typename C>
class Image : public internal::ImageBase, public config::CommonBase {
public:
  void create(Vec2i size);
  C& operator[](Vec2i pos);
  void* data() override;
  Vec2i dimension() override;
  
private:
  std::unique_ptr<C[]> m_data;
  Vec2i m_size;
};

class ImageBox : public config::CommonBase {
public:
  template <typename C>
  ImageBox(Image<C>&& image);

  template <typename C>
  ImageBox& operator=(Image<C>&& image);

  void* data();
  Vec2i dimension();

  template <typename C>
  Color<C>& get();

private:
  std::shared_ptr<internal::ImageBase> m_img;
};

} // namespace lumina

#include "Image.tpp"