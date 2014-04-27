#pragma once
/**
 * \file half.hpp
 * This file is part of the Lumina Graphics Framework [L/util]
 * 
 * \author Sebastian von Ohr
 * 
 * Defines the half type, which is a 16 bit float type. For more information:
 * http://en.wikipedia.org/wiki/Half-precision_floating-point_format
 */
#include <limits>
#include <cstdint>

// check float implementation
static_assert(
  std::numeric_limits<float>::is_iec559,
  "Half-precision float implementation requires IEC 559 compliant format");

namespace lumina {

class half {
public:
  // constructors
  half() : m_data(0) {}

  half(float v) {
    uint32_t in;
    memcpy(&in, &v, 4);

    // extract components
    m_data = (in >> 16) & 0x8000;   // sign bit
    uint8_t ex = (in >> 23) & 0xFF; // exponent
    uint32_t ma = in & 0x007FFFFF;  // mantissa

    if(ex == 255 && ma != 0) {  // NaN
      m_data |= 0x1F << 10;
      m_data |= 1;
    } 
    else if(ex > 127 + 15) {  // to big values
      m_data |= 0x1F << 10;
    } 
    else if(ex < 127 - 24) {  // to small values
      m_data |= 0;
    } 
    else if(ex < 127 - 14) {  // conversion to subnormal
      m_data |= (ma | 0x00800000) >> (126 - ex);
    } 
    else {
      m_data |= (ex - 127 + 15) << 10;
      m_data |= ma >> 13;
    }
  }

  // conversion to float
  operator float() const {
    // extract components
    uint32_t out = (m_data & 0x8000) << 16; // sign bit
    uint8_t ex = (m_data >> 10) & 0x1F;     // exponent
    uint16_t ma = m_data & 0x03FF;          // mantissa

    if(ex == 0x1F) {  // inf or NaN
      out |= 0xFF << 23;
      if(ma)
        out |= 1;      // NaN
    } 
    else if(ex == 0) {  // zero or subnormal
      if(ma != 0) // normalize number
      {
        for(ex = 0; (ma & 0x0400) == 0; ++ex)
          ma <<= 1;
        out |= (0x71 - ex) << 23;
        out |= (ma & 0x03FF) << 13;
      }
    } 
    else {  // normalized values
      out |= (ex + 127 - 15) << 23;
      out |= ma << 13;
    }
    float outf;
    memcpy(&outf, &out, 4);
    return outf;
  }

private:
  uint16_t m_data;
};

} // namespace lumina

// traits
namespace std {
template <> struct is_floating_point<engine::half> : true_type {};
}
