#pragma once

#include <GL/glew.h>

#include <cstdint>

namespace lumina {

enum class LVertexComponent {
  None,
  Pos3D,
  Pos2D,
  Color,
  Normal,
  Tangent,
  TexCoord
};

class LVertexLayout {
public:
  LVertexLayout() : m_delegate(nullptr) {}


private:
  void (*m_delegate)();

  LVertexLayout(void(*delegate)()) : m_delegate(delegate) {}

  void apply() {
    if(m_delegate) {
      m_delegate();
    }
  }

  template<LVertexComponent... Comps>
  static void applyVertexLayout() {
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
  }

  // friend declarations
  template <LVertexComponent...>
  friend LVertexLayout createVertexLayout();
  friend class LRawMesh;
};


template <LVertexComponent... Components>
LVertexLayout createVertexLayout() {
  return LVertexLayout(&LVertexLayout::applyVertexLayout<Components...>);
}

} // namespace lumina