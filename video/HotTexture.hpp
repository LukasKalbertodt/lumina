#pragma once

#include "TexType.hpp"
#include "TexParam.hpp"
#include "Texture.hpp"
#include "../config/BaseProxy.hpp"

namespace lumina {

template <TexType TT>
class HotTexture : public config::CommonBase {
public:
  ~HotTexture(); 

  void fill(void* data);


  TexParam& param;
private:
  Texture<TT>& m_tex;
  bool m_genMipMaps;

  HotTexture(Texture<TT>& ref);
  void fillSubData(GLenum format, GLenum type, void* data);

  friend Texture<TT>;
};

}

#include "HotTexture.tpp"