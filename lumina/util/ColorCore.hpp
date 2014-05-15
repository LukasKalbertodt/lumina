#pragma once
/**
 * \file ColorCore.hpp
 * This file is part of the Lumina Graphics Framework [L/util]
 *
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 *
 * This file will define LColor and various color functions. In most cases you
 * should include Color.hpp instead, which provides additional helper
 * functions (but has more dependencies).
 */
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <string>

namespace lumina {

// forward declare half float type (see util/half.hpp)
class half;

template <class T, class U>
inline T clamp(U v)
{
  if(v > std::numeric_limits<T>::max())
    return std::numeric_limits<T>::max();
  else if(v < std::numeric_limits<T>::min())
    return std::numeric_limits<T>::min();
  else
    return static_cast<T>(v);
}


namespace internal {




template <typename T, typename Enable = void> struct ColorTraits;

// specialization for floating point
template <typename T>
struct ColorTraits<T,
                   typename std::enable_if<std::is_floating_point<T>::value,
                                           void>::type> {
  static constexpr bool isFloatingPoint = true;
  static constexpr T maxColor = 1.f;
};

// specialization for integral types
template <typename T>
struct ColorTraits<T,
                   typename std::enable_if<std::is_integral<T>::value,
                                           void>::type> {
  static constexpr bool isFloatingPoint = false;
  static constexpr T maxColor = std::numeric_limits<T>::max();
};






template <typename T, bool Alpha>
struct ColorImpl;

template <typename T>
struct ColorImpl<T, true> {
  union {
    struct {
      T r, g, b, a;
    };
    T data[4];
  };

  ColorImpl(T r, T g, T b, T a = ColorTraits<T>::maxColor)
    : r(r), g(g), b(b), a(a) {}
  ColorImpl() : r(T(0)), g(T(0)), b(T(0)), a(ColorTraits<T>::maxColor) {}
};

template <typename T>
struct ColorImpl<T, false> {
  union {
    struct {
      T r, g, b;
    };
    T data[3];
  };

  ColorImpl(T r, T g, T b) : r(r), g(g), b(b) {}
  ColorImpl() : r(T(0)), g(T(0)), b(T(0)) {}
};

}

template <typename T, bool A = false>
struct Color : public internal::ColorImpl<T, A> {
  using internal::ColorImpl<T, A>::ColorImpl;
  using type = T;
  static constexpr bool alpha = A;


  bool operator==(Color<T, A> other) {
    bool same = true;
    for(int i = 0; i < sizeof(this->data)/sizeof(this->data[0]); ++i) {
      same = same && (this->data[i] == other.data[i]);
    }
    return same;
  }

  bool operator!=(Color<T, A> other) {
    return !(*this == other);
  }

  T& operator[](std::size_t index) {
    if(index >= 4)
      throw std::out_of_range("Invalid subscript");
    return this->data[index];
  }

  T operator[](std::size_t index) const {
    if(index >= 4)
      throw std::out_of_range("Invalid subscript");
    return this->data[index];
  }
};



using Color8 = Color<uint8_t>;
using Color8A = Color<uint8_t, true>;
using Color16 = Color<uint16_t>;
using Color16A = Color<uint16_t, true>;
using Color32 = Color<uint32_t>;
using Color32A = Color<uint32_t, true>;
using Color32f = Color<float>;
using Color32fA = Color<float, true>;
using Color16f = Color<half>;
using Color16fA = Color<half, true>;


/**
 * @brief Creates a color from propertions values
 * 
 * @tparam Tout Color type
 * @return The created color
 */
// template <typename Tout, typename Enable = void>
// Tout makeColor(float r, float g, float b, float a = 1.f);

template <typename Tout>
typename std::enable_if<std::is_integral<typename Tout::type>::value,
                        Tout>::type
makeColor(float r, float g, float b, float a = 1.f) {
  return Tout(r * internal::ColorTraits<typename Tout::type>::maxColor,
              g * internal::ColorTraits<typename Tout::type>::maxColor,
              b * internal::ColorTraits<typename Tout::type>::maxColor,
              a * internal::ColorTraits<typename Tout::type>::maxColor);
}
template <typename Tout>
typename std::enable_if<std::is_floating_point<typename Tout::type>::value,
                        Tout>::type
makeColor(float r, float g, float b, float a = 1.f) {
  return Tout(r, g, b, a);
}

/**
 * @brief Returns the proportion of the given value to the max value of that
 *        color type
 */
template <typename T>
float colorProportion(T v) {
  return (v / static_cast<float>(internal::ColorTraits<T>::maxColor)); 
}

template <typename Tout, typename Tin>
Tout convertChannelType(Tin in) {
  return colorProportion(in) * internal::ColorTraits<Tout>::maxColor;
}

/**
 * @brief Converts one color type to another one using float proportions 
 *        (expect minimal loss in precision)
 *        
 * @param in The color to convert
 * @tparam Tdst Destionation color type
 */
template <typename Tdst, typename Tsrc>
typename std::enable_if<Tdst::A, Tdst>::type color_cast(Color<Tsrc, true> in) {
  return Tdst(convertChannelType<typename Tdst::type>(in.r),
              convertChannelType<typename Tdst::type>(in.g),
              convertChannelType<typename Tdst::type>(in.b),
              convertChannelType<typename Tdst::type>(in.a));
}
template <typename Tdst, typename Tsrc>
typename std::enable_if<!Tdst::A, Tdst>::type color_cast(Color<Tsrc, true> in) {
  return Tdst(convertChannelType<typename Tdst::type>(in.r),
              convertChannelType<typename Tdst::type>(in.g),
              convertChannelType<typename Tdst::type>(in.b));
}
template <typename Tdst, typename Tsrc>
Tdst color_cast(Color<Tsrc, false> in) {
  return Tdst(convertChannelType<typename Tdst::type>(in.r),
              convertChannelType<typename Tdst::type>(in.g),
              convertChannelType<typename Tdst::type>(in.b));
}


/**
 * @brief Blends two colors additive
 * @details Each color is weighted by it's own alpha value. Both weighted 
 *          colors are added together. The result may exceed 1.f, when using 
 *          a floating point color type.
 */
template <typename T>
Color<T, true> blendAdditive(Color<T, true> lh, Color<T, true> rh) {
  float lha = lh.a / 255.f;
  float rha = rh.a / 255.f;

  // The float result is implicit casted to T and will clamped automatic.
  return Color<T, true>(lh.r * lha + rh.r * rha,
                        lh.g * lha + rh.g * rha,
                        lh.b * lha + rh.b * rha,
                        lh.a + rh.a);
}

/**
 * @brief Blends two colors via alpha blend
 * @details The alpha of the lh color is ignored (lh is background). The rh 
 *          color (foreground) is weighted with it's own alpha value and the
 *          lh color is weighted by the inverse alpha value of rh (1-rh.alpha).
 *          Won't exceed the standard color range.
 */
template <typename T>
Color<T, true> blendAlpha(Color<T, true> lh, Color<T, true> rh) {
  float alpha = rh.a / 255.f;
  float ainv = 1 - alpha;

  // The float result is implicit casted to T and will clamped automatic.
  return Color<T, true>(lh.r * ainv + rh.r * alpha,
                        lh.g * ainv + rh.g * alpha,
                        lh.b * ainv + rh.b * alpha,
                        lh.a * ainv + rh.a * alpha);
}

// /**
//  * @brief Blends two colors with specific weight values
//  * @details Each color is weighted by the given alpha parameter. Won't exceed
//  *          standard color range.
//  */
// template <typename T>
// LColor<T> weightedBlend(LColor<T> lh,
//                         float lhAlpha,
//                         LColor<T> rh,
//                         float rhAlpha) {
//   // normalize weight values
//   if(lhAlpha < 0.f)
//     lhAlpha = 0.f;
//   if(rhAlpha < 0.f)
//     rhAlpha = 0.f;

//   float sum = lhAlpha + rhAlpha;
//   if(sum > 1.f) {
//     lhAlpha /= sum;
//     rhAlpha /= sum;
//   }

//   return LColor<T>(lh.r * lhAlpha + rh.r * rhAlpha,
//                    lh.g * lhAlpha + rh.g * rhAlpha,
//                    lh.b * lhAlpha + rh.b * rhAlpha,
//                    lh.a * lhAlpha + rh.a * rhAlpha);
// }









} // namespace lumina