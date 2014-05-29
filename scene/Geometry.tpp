#include "../util/VariadicTools.hpp"
#include "../video/PrimitiveType.hpp"

namespace lumina {

namespace internal {

struct VPoint {
  VPoint(Vec3f pos, Vec3f nor, Vec2f tex)
    : position(pos), normal(nor), texUV(tex) {}

  template <VChan C> typename VChanHelper<C>::type get() const;

  Vec3f position;
  Vec3f normal;
  Vec2f texUV;
};

template <> Vec3f VPoint::get<VChan::Position>() const { return position; }
template <> Vec3f VPoint::get<VChan::Normal>() const { return normal; }
template <> Vec2f VPoint::get<VChan::TexUV>() const { return texUV; }


template <VChan... Cs, typename T>
void fillData(T slot, const VPoint& data) {
  slot.set(data.get<Cs>()...);
}

}

template <VChan... Cs> 
Mesh createBox(Vec3f size) {
  static_assert(sizeof...(Cs) > 0,
                "[createBox] You must specify vertex channels to be filled!");

  using namespace internal;

  Mesh out;

  // 6 faces, 4 points per face
  int bufsize = internal::VChansHelper<Cs...>::size * 6 * 4;
  out.create(bufsize);

  out.prime<typename VChanHelper<Cs>::type...>([&](
    HotMesh<typename VChanHelper<Cs>::type...>& hot) {
    // fill vertex buffer with corner-points

    // face positiv z
    fillData<Cs...>(hot.vertex[0],
                    VPoint(Vec3f(-size.x, size.y, size.z),
                           Vec3f(0, 0, 1),
                           Vec2f(1, 1)));
    fillData<Cs...>(hot.vertex[1],
                    VPoint(Vec3f(-size.x, -size.y, size.z),
                           Vec3f(0, 0, 1),
                           Vec2f(0, 1)));
    fillData<Cs...>(hot.vertex[2],
                    VPoint(Vec3f(size.x, size.y, size.z),
                           Vec3f(0, 0, 1),
                           Vec2f(1, 0)));
    fillData<Cs...>(hot.vertex[3],
                    VPoint(Vec3f(size.x, -size.y, size.z),
                           Vec3f(0, 0, 1),
                           Vec2f(0, 0)));
    
    hot.setPrimitiveType(PrimitiveType::TriangleStrip);
    hot.applyVertexLayout();
  });

  return out;
}

}