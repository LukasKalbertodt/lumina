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

  // Should runtime checks be performed, that will check that the correct 
  // textures are primed when drawing?
  constexpr bool debugTextureDrawChecks = true;

  // Should runtime checks be performed, that will check if a texture unit
  // is primed multiple times?
  constexpr bool debugTexturePrimeChecks = true;
}

} // namespace lumina