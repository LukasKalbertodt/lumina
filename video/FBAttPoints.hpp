#pragma once

#include "TexFormat.hpp"
#include "Texture.hpp"
#include "../service/StaticLogger.hpp"

namespace lumina {
namespace internal {

struct ColorAttPoint {
  GLuint handle;
  TexFormat format;

  ColorAttPoint() : handle(0) {}
};

class ColorAttSlot {
public:
  ColorAttSlot(ColorAttPoint& point, bool& needsUpdate)
    : m_point(point), m_needsUpdate(needsUpdate) {}

  void operator=(const Tex2D& tex) {
    // check if the format is correct
    auto format = tex.getFormat();
    if(format == TexFormat::D16 || format == TexFormat::D32
       || format == TexFormat::D24S8) {
      slogAndThrow<InvalidArgEx>(
        "[FrameBuffer] You can not attach a texture "
        "with depth or stencil format to a color attachment point!");
    }

    // assign values if the values are distinct
    if(m_point.handle != tex.nativeHandle()) {
      m_point.handle = tex.nativeHandle();
      m_point.format = tex.getFormat();
      m_needsUpdate = true;
    }
  }

private:
  ColorAttPoint& m_point;
  bool& m_needsUpdate;
};


class ColorAttSet {
public:
  ColorAttSet(std::vector<ColorAttPoint>& atts, bool& needsUpdate)
    : m_atts(atts), m_needsUpdate(needsUpdate) {}

  ColorAttSlot operator[](int index) {
    if(index >= m_atts.size()) {
      slogAndThrow<OutOfRangeEx>("[FrameBuffer] Index<", index, 
                                 "> out of bounds<", m_atts.size(), ">!");
    }
    return ColorAttSlot(m_atts[index], m_needsUpdate);
  }


private:
  std::vector<ColorAttPoint>& m_atts;
  bool& m_needsUpdate;
};


}
}