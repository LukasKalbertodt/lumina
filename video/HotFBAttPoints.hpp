#pragma once

#include "FBAttPoints.hpp"
#include "TexFormat.hpp"
#include "Texture.hpp"
#include "../util/ColorCore.hpp"
#include "../service/StaticLogger.hpp"

namespace lumina {
namespace internal {

class HotColorAttSlot {
public:
  HotColorAttSlot(ColorAttPoint& point, int index)
    : m_point(point), m_index(index) {}

  void clear(Color32A color) {
    auto f = m_point.format;
    if(!(f == TexFormat::R8 || f == TexFormat::RGB8 || f == TexFormat::RGBA8)) {
      slogAndThrow<InvalidArgEx>("[HotFrameBuffer] You can not clear a "
                                 "floating point texture with a integer color "
                                 "format!");
    }
    GLuint d[4] = {color.r, color.g, color.b, color.a};
    glClearBufferuiv(GL_COLOR, m_index, d);
  }

  void clear(Color32fA color) {
    auto f = m_point.format;
    if(f == TexFormat::R8 || f == TexFormat::RGB8 || f == TexFormat::RGBA8) {
      slogAndThrow<InvalidArgEx>("[HotFrameBuffer] You can not clear a integer "
                                 "texture with a floating point color format!");
    }
    GLfloat d[4] = {color.r, color.g, color.b, color.a};
    glClearBufferfv(GL_COLOR, m_index, d);
  }


private:
  ColorAttPoint& m_point;
  int m_index;
};


class HotColorAttSet {
public:
  HotColorAttSet(std::vector<ColorAttPoint>& atts)
    : m_atts(atts) {}

  HotColorAttSlot operator[](int index) {
    if(index >= m_atts.size()) {
      slogAndThrow<OutOfRangeEx>("[FrameBuffer] Index<", index, 
                                 "> out of bounds<", m_atts.size(), ">!");
    }
    return HotColorAttSlot(m_atts[index], index);
  }


private:
  std::vector<ColorAttPoint>& m_atts;
};


}
}