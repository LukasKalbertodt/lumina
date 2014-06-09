#pragma once

#include "../config/BaseProxy.hpp"
#include "../config/LConfig.hpp"
#include "../util/Vector.hpp"

#include <memory>

namespace lumina {

template <typename C>
class Image : public config::CommonBase {
public:
  void create(Vec2i size);
  C& operator[](Vec2i pos);
  C* data();
  
private:
  std::unique_ptr<C[]> m_data;
  Vec2i m_size;

};

} // namespace lumina

#include "Image.tpp"