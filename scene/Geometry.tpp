#include "../util/VariadicTools.hpp"
#include "../video/PrimitiveType.hpp"

// #include <iostream>
// using namespace std;

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
VertexSeq createBox(Vec3f size) {
  static_assert(sizeof...(Cs) > 0,
                "[createBox] You must specify vertex channels to be filled!");

  using namespace internal;

  VertexSeq out;

  // 6 faces, 4 points per face
  int vbufsize = internal::VChansHelper<Cs...>::size * 6 * 4;
  // 6 faces * 4 points + 5 primitive restart
  int ibufsize = 6 * 4 + 5;
  out.create(vbufsize, ibufsize);

  out.prime<typename VChanHelper<Cs>::type...>([&](
    HotVertexSeq<typename VChanHelper<Cs>::type...>& hot) {
    // fill vertex buffer with corner-points

    // ---------- face positiv z ---------------
    fillData<Cs...>(hot.vertex[0],
                    VPoint(Vec3f(-size.x, size.y, size.z),
                           Vec3f(0, 0, 1),
                           Vec2f(0, 0)));
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
                           Vec2f(1, 1)));
    hot.index[0] = 0;
    hot.index[1] = 1;
    hot.index[2] = 2;
    hot.index[3] = 3;


    hot.index[4] = GLIndex::PrimitiveRestart;
    // ---------- face positiv x ---------------
    fillData<Cs...>(hot.vertex[4],
                    VPoint(Vec3f(size.x, size.y, size.z),
                           Vec3f(1, 0, 0),
                           Vec2f(0, 0)));
    fillData<Cs...>(hot.vertex[5],
                    VPoint(Vec3f(size.x, -size.y, size.z),
                           Vec3f(1, 0, 0),
                           Vec2f(0, 1)));
    fillData<Cs...>(hot.vertex[6],
                    VPoint(Vec3f(size.x, size.y, -size.z),
                           Vec3f(1, 0, 0),
                           Vec2f(1, 0)));
    fillData<Cs...>(hot.vertex[7],
                    VPoint(Vec3f(size.x, -size.y, -size.z),
                           Vec3f(1, 0, 0),
                           Vec2f(1, 1)));
    hot.index[5] = 4;
    hot.index[6] = 5;
    hot.index[7] = 6;
    hot.index[8] = 7;



    hot.index[9] = GLIndex::PrimitiveRestart;
    // ---------- face negative z ---------------
    fillData<Cs...>(hot.vertex[8],
                    VPoint(Vec3f(size.x, size.y, -size.z),
                           Vec3f(0, 0, -1),
                           Vec2f(0, 0)));
    fillData<Cs...>(hot.vertex[9],
                    VPoint(Vec3f(size.x, -size.y, -size.z),
                           Vec3f(0, 0, -1),
                           Vec2f(0, 1)));
    fillData<Cs...>(hot.vertex[10],
                    VPoint(Vec3f(-size.x, size.y, -size.z),
                           Vec3f(0, 0, -1),
                           Vec2f(1, 0)));
    fillData<Cs...>(hot.vertex[11],
                    VPoint(Vec3f(-size.x, -size.y, -size.z),
                           Vec3f(0, 0, -1),
                           Vec2f(1, 1)));
    hot.index[10] = 8;
    hot.index[11] = 9;
    hot.index[12] = 10;
    hot.index[13] = 11;



    hot.index[14] = GLIndex::PrimitiveRestart;
    // ---------- face negative x ---------------
    fillData<Cs...>(hot.vertex[12],
                    VPoint(Vec3f(-size.x, size.y, -size.z),
                           Vec3f(-1, 0, 0),
                           Vec2f(0, 0)));
    fillData<Cs...>(hot.vertex[13],
                    VPoint(Vec3f(-size.x, -size.y, -size.z),
                           Vec3f(-1, 0, 0),
                           Vec2f(0, 1)));
    fillData<Cs...>(hot.vertex[14],
                    VPoint(Vec3f(-size.x, size.y, size.z),
                           Vec3f(-1, 0, 0),
                           Vec2f(1, 0)));
    fillData<Cs...>(hot.vertex[15],
                    VPoint(Vec3f(-size.x, -size.y, size.z),
                           Vec3f(-1, 0, 0),
                           Vec2f(1, 1)));
    hot.index[15] = 12;
    hot.index[16] = 13;
    hot.index[17] = 14;
    hot.index[18] = 15;


    hot.index[19] = GLIndex::PrimitiveRestart;
    // ---------- face positive y ---------------
    fillData<Cs...>(hot.vertex[16],
                    VPoint(Vec3f(-size.x, size.y, -size.z),
                           Vec3f(0, 1, 0),
                           Vec2f(0, 0)));
    fillData<Cs...>(hot.vertex[17],
                    VPoint(Vec3f(-size.x, size.y, size.z),
                           Vec3f(0, 1, 0),
                           Vec2f(0, 1)));
    fillData<Cs...>(hot.vertex[18],
                    VPoint(Vec3f(size.x, size.y, -size.z),
                           Vec3f(0, 1, 0),
                           Vec2f(1, 0)));
    fillData<Cs...>(hot.vertex[19],
                    VPoint(Vec3f(size.x, size.y, size.z),
                           Vec3f(0, 1, 0),
                           Vec2f(1, 1)));
    hot.index[20] = 16;
    hot.index[21] = 17;
    hot.index[22] = 18;
    hot.index[23] = 19;


    hot.index[24] = GLIndex::PrimitiveRestart;
    // ---------- face negative y ---------------
    fillData<Cs...>(hot.vertex[20],
                    VPoint(Vec3f(size.x, -size.y, size.z),
                           Vec3f(0, -1, 0),
                           Vec2f(0, 0)));
    fillData<Cs...>(hot.vertex[21],
                    VPoint(Vec3f(-size.x, -size.y, size.z),
                           Vec3f(0, -1, 0),
                           Vec2f(0, 1)));
    fillData<Cs...>(hot.vertex[22],
                    VPoint(Vec3f(size.x, -size.y, -size.z),
                           Vec3f(0, -1, 0),
                           Vec2f(1, 0)));
    fillData<Cs...>(hot.vertex[23],
                    VPoint(Vec3f(-size.x, -size.y, -size.z),
                           Vec3f(0, -1, 0),
                           Vec2f(1, 1)));
    hot.index[25] = 20;
    hot.index[26] = 21;
    hot.index[27] = 22;
    hot.index[28] = 23;
    


    hot.setPrimitiveType(PrimitiveType::TriangleStrip);
    hot.applyVertexLayout();

    // auto* buf = static_cast<float*>(hot.vertex.buf());
    // for(int i = 0; i < 20; i++) {
    //   cout << *buf << endl;
    //   buf++;
    // }


  });

  return out;
}

}