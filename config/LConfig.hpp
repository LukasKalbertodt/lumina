#pragma once
/**
 * File: LConfig.hpp
 * Is included after LCommon.hpp
 */

namespace lumina {


namespace config {
  /*****************************************************************************
   * Modifies the behavior of the logger
   */
  // control use of cout and cerr
  constexpr bool useLogStandardIO = true;

  // should runtime bound checks be performed?
  constexpr bool debugBoundChecks = true;
}

} // namespace lumina