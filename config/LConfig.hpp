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

  // set to true to ignore logs with level Debug (the compiler 
  // can optimize the calls away)
  constexpr bool ignoreDebugLogs = false;

  // print debug logs for events that happen every frame?
  constexpr bool logDebugEveryFrame = false;



  // should runtime bound checks be performed?
  constexpr bool debugBoundChecks = true;

  // Should runtime checks be performed, that will check that the correct 
  // textures are primed when drawing?
  constexpr bool debugTextureDrawChecks = true;

  // Should runtime checks be performed, that will check if a texture unit
  // is primed multiple times?
  constexpr bool debugTexturePrimeChecks = true;

  // When creating a GLObject, should it test if a context is current?
  constexpr bool debugContextCurrentCheck = true;

  // check if a framebuffer is primed in draw()?
  constexpr bool debugDrawFrameBufferCheck = true;

  // reset all state/unbind stuff?
  constexpr bool resetGLState = true;
}

} // namespace lumina