#pragma once
/**
 * \file LColorCore.hpp
 * This file is part of the Lumina Graphics Framework [L/util]
 *
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 *
 * This file will define LColor and various color functions. In most cases you
 * should include LColor.hpp instead, which provides additional helper
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

/**
 * @brief Internal traits for color types
 */
template <typename T, typename Enable = void> struct LXColorTraitsImpl;

// specialization for floating point
template <typename T>
struct LXColorTraitsImpl<T,
                         typename std::enable_if<std::is_floating_point<T>::value,
                                                 void>::type> {
  static constexpr bool isFloatingPoint = true;
  static constexpr T maxColor = 1.f;
};

// specialization for integral types
template <typename T>
struct LXColorTraitsImpl<T,
                         typename std::enable_if<std::is_integral<T>::value,
                                                 void>::type> {
  static constexpr bool isFloatingPoint = false;
  static constexpr T maxColor = std::numeric_limits<T>::max();
};

/**
 * @brief Traits for color types (currently the same as LXColorTraitsImpl)
 */
template <typename T> struct LColorTraits : public LXColorTraitsImpl<T> {};



template <typename T>
struct LColor {
  typedef T type;
  T r, g, b, a;

  LColor() 
    : LColor(0,0,0) {}

  LColor(T r, T g, T b, T a = LColorTraits<T>::maxColor)
    : r(r), g(g), b(b), a(a) {}

  bool operator==(LColor<T> other) {
    return (r == other.r && g == other.g && b == other.b && a == other.a);
  }

  bool operator!=(LColor<T> other) {
    return !(*this == other);
  }

  T& operator[](std::size_t index) {
    if(index >= 4)
      throw std::out_of_range("Invalid subscript");
    return reinterpret_cast<T*>(this)[index];
  }

  T operator[](std::size_t index) const {
    if(index >= 4)
      throw std::out_of_range("Invalid subscript");
    return reinterpret_cast<T*>(this)[index];
  }
};

using Color8 = LColor<uint8_t>;
using Color16 = LColor<uint16_t>;
using Color32 = LColor<uint32_t>;
using Color32f = LColor<float>;
using Color16f = LColor<half>;


/**
 * @brief Creates a color from propertions values
 * 
 * @tparam Tout Color type
 * @return The created color
 */
template <typename Tout>
Tout makeColor(float r, float g, float b, float a = 1.f) {
  return Tout(r * LColorTraits<typename Tout::type>::maxColor,
              g * LColorTraits<typename Tout::type>::maxColor,
              b * LColorTraits<typename Tout::type>::maxColor,
              a * LColorTraits<typename Tout::type>::maxColor);
}
template <>
LColor<float> makeColor<LColor<float>>(float r, float g, float b, float a) {
  return LColor<float>(r, g, b, a);
}

/**
 * @brief Returns the proportion of the given value to the max value of that
 *        color type
 */
template <typename T>
float colorProportion(T v) {
  return (v / static_cast<float>(LColorTraits<T>::maxColor)); 
}

template <typename Tout, typename Tin>
Tout convertChannelType(Tin in) {
  return colorProportion(in) * LColorTraits<Tout>::maxColor;
}

/**
 * @brief Converts one color type to another one using float proportions 
 *        (expect minimal loss in precision)
 *        
 * @param in The color to convert
 * @tparam Tdst Destionation color type
 */
template <typename Tdst, typename Tsrc>
Tdst color_cast(LColor<Tsrc> in) {
  return Tdst(convertChannelType<typename Tdst::type>(in.r),
              convertChannelType<typename Tdst::type>(in.g),
              convertChannelType<typename Tdst::type>(in.b),
              convertChannelType<typename Tdst::type>(in.a));
}


/**
 * @brief Blends two colors additive
 * @details Each color is weighted by it's own alpha value. Both weighted 
 *          colors are added together. The result may exceed 1.f, when using 
 *          a floating point color type.
 */
template <typename T>
LColor<T> blendAdditive(LColor<T> lh, LColor<T> rh) {
  float lha = lh.a / 255.f;
  float rha = rh.a / 255.f;

  // The float result is implicit casted to T and will clamped automatic.
  return LColor<T>(lh.r * lha + rh.r * rha,
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
LColor<T> blendAlpha(LColor<T> lh, LColor<T> rh) {
  float alpha = rh.a / 255.f;
  float ainv = 1 - alpha;

  // The float result is implicit casted to T and will clamped automatic.
  return LColor<T>(lh.r * ainv + rh.r * alpha,
                   lh.g * ainv + rh.g * alpha,
                   lh.b * ainv + rh.b * alpha,
                   lh.a * ainv + rh.a * alpha );
}

/**
 * @brief Blends two colors with specific weight values
 * @details Each color is weighted by the given alpha parameter. Won't exceed
 *          standard color range.
 */
template <typename T>
LColor<T> weightedBlend(LColor<T> lh,
                        float lhAlpha,
                        LColor<T> rh,
                        float rhAlpha) {
  // normalize weight values
  if(lhAlpha < 0.f)
    lhAlpha = 0.f;
  if(rhAlpha < 0.f)
    rhAlpha = 0.f;

  float sum = lhAlpha + rhAlpha;
  if(sum > 1.f) {
    lhAlpha /= sum;
    rhAlpha /= sum;
  }

  return LColor<T>(lh.r * lhAlpha + rh.r * rhAlpha,
                   lh.g * lhAlpha + rh.g * rhAlpha,
                   lh.b * lhAlpha + rh.b * rhAlpha,
                   lh.a * lhAlpha + rh.a * rhAlpha);
}





















} // namespace lumina