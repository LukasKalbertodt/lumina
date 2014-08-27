#include "../util/VariadicTools.hpp"
#include "../video/PrimitiveType.hpp"

#include "../service/StaticLogger.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace lumina {

namespace internal {

struct VPoint {
  VPoint(Vec3f pos, Vec3f nor, Vec2f tex)
    : position(pos), normal(nor), texUV(tex) {}

  template <VAttr C> typename VAttrHelper<C>::type get() const;

  Vec3f position;
  Vec3f normal;
  Vec2f texUV;
};

template <> inline Vec3f VPoint::get<VAttr::Position>() const {
  return position;
}
template <> inline Vec3f VPoint::get<VAttr::Normal>() const { 
  return normal; 
}
template <> inline Vec2f VPoint::get<VAttr::TexUV>() const { 
  return texUV; 
}



template <VAttr... Cs, typename T>
void fillData(T slot, const VPoint& data) {
  slot.set(data.get<Cs>()...);
}

}



template <VAttr... Cs> 
VertexSeq<typename internal::VAttrHelper<Cs>::type...> createBox(Vec3f size) {
  static_assert(sizeof...(Cs) > 0,
                "[createBox] You must specify vertex channels to be filled!");

  using namespace internal;

  VertexSeq<typename VAttrHelper<Cs>::type...> out;

  // vertexCount = 6 faces * 4 points per face
  // indexCount = 6 faces * 4 points + 5 primitive restart
  out.create(6 * 4, 6 * 4 + 5);

  out.prime([&](HotVertexSeq<typename VAttrHelper<Cs>::type...>& hot) {
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
  });

  return out;
}


template <VAttr... Cs>
VertexSeq<typename internal::VAttrHelper<Cs>::type...> createSphere(
  float radius, int thetaSteps, int phiSteps) {
  static_assert(sizeof...(Cs) > 0,
                "[createBox] You must specify vertex channels to be filled!");

  using namespace internal;

  constexpr float PI = 3.1415926;

  VertexSeq<typename VAttrHelper<Cs>::type...> out;

  int vertexCount = 2 + (thetaSteps - 1) * phiSteps;
  int indexCount = 2 * phiSteps * 4
                   + ((thetaSteps - 2) * 2 * (phiSteps + 1) + (thetaSteps - 2));
  // vertexCount = 2 poles
  // indexCount = 
  out.create(vertexCount, indexCount);
  slog("Count: ", vertexCount);

  out.prime([&](HotVertexSeq<typename VAttrHelper<Cs>::type...>& hot) {
    // north pole
    fillData<Cs...>(hot.vertex[0],
                    VPoint(Vec3f(0, radius, 0),
                           Vec3f(0, 1, 0),
                           Vec2f(0.5, 0)));
    // south pole
    fillData<Cs...>(hot.vertex[vertexCount - 1],
                    VPoint(Vec3f(0, -radius, 0),
                           Vec3f(0, -1, 0),
                           Vec2f(0.5, 1)));

    for(int thetaIt = 1; thetaIt < thetaSteps; ++thetaIt) {
      float theta = (thetaIt * PI) / (thetaSteps);

      for(int phiIt = 0; phiIt < phiSteps; ++phiIt) {
        float phi = (phiIt * PI * 2) / phiSteps;

        Vec3f norm(cos(phi) * sin(theta), cos(theta), sin(phi) * sin(theta));

        int index = 1 + phiIt + (thetaIt - 1) * phiSteps;
        std::cout << std::setprecision(3);
        Vec2f uv = Vec2f(static_cast<float>(phiIt) / phiSteps,
                         static_cast<float>(thetaIt) / thetaSteps);
        // Vec2i uv = Vec2i(1, 0);

        fillData<Cs...>(hot.vertex[index],
                        VPoint(norm * radius, norm, uv));
      }
    }

    int ind = 0;

    // ----- north pole -----
    hot.index[ind++] = 0;
    hot.index[ind++] = 1;
    hot.index[ind++] = phiSteps;
    hot.index[ind++] = GLIndex::PrimitiveRestart;

    for(int phiIt = 1; phiIt < phiSteps; ++phiIt) {
      hot.index[ind++] = 0;
      hot.index[ind++] = phiIt + 1;
      hot.index[ind++] = phiIt;
      hot.index[ind++] = GLIndex::PrimitiveRestart;
    }


    // ----- main -----
    for(int level = 0; level < thetaSteps - 2; ++level) {
      int lowOffset = 1 + level * phiSteps;
      int highOffset = 1 + (level + 1) * phiSteps;

      for(int piece = 0; piece < phiSteps; ++piece) {
        hot.index[ind++] = highOffset + piece;
        hot.index[ind++] = lowOffset + piece;
      }
      hot.index[ind++] = highOffset;
      hot.index[ind++] = lowOffset;
      hot.index[ind++] = GLIndex::PrimitiveRestart;
    }


    // ------ south pole ---------
    int lastStripeOffset = (thetaSteps - 2) * phiSteps;
    hot.index[ind++] = vertexCount - 1;
    hot.index[ind++] = vertexCount - 2;
    hot.index[ind++] = lastStripeOffset + 1;
    hot.index[ind++] = GLIndex::PrimitiveRestart;

    for(int phiIt = 1; phiIt < phiSteps; ++phiIt) {
      hot.index[ind++] = vertexCount - 1;
      hot.index[ind++] = lastStripeOffset + phiIt;
      hot.index[ind++] = lastStripeOffset + phiIt + 1;
      hot.index[ind++] = GLIndex::PrimitiveRestart;
    }
  });

  return out;
}

}