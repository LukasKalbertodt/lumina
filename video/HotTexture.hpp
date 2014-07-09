#pragma once

#include "GLObject.hpp"
#include "TexType.hpp"
#include "TexParam.hpp"
#include "Texture.hpp"
#include "../config/BaseProxy.hpp"

namespace lumina {

template <TexType TT>
class HotTexture : public GLObject {
public:
  ~HotTexture(); 

  void fill(void* data);


  TexParam& param;
private:
  Texture<TT>& m_tex;
  int m_texUnit;
  bool m_genMipMaps;

  HotTexture(Texture<TT>& ref, int texUnit);
  void fillSubData(GLenum format, GLenum type, void* data);

  friend Texture<TT>;
};

}

#include "HotTexture.tpp"