#pragma once
/**
 * File: LConfig.hpp
 * Is included after LCommon.hpp
 */

namespace lumina {


/*******************************************************************************
 * Modifies the behavior of the logger
 */
// control use of cout and cerr
namespace config {
  constexpr bool useLogStandardIO = true;
}

} // namespace lumina