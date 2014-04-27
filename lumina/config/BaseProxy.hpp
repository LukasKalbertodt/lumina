#pragma once
/**
 * \file BaseProxy.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file is included by almost every file in the engine.
 * This file MUST:
 *  - TODO -
 */
#define USE_CONTEXT true

// if the service context is used, there is one service for each context
#if USE_CONTEXT
  #include "../core/LContextBase.hpp"

  namespace lumina {
  namespace config {
    typedef LContextBase CommonBase;
  }
  }

// if the service context is not used, every service is a singleton
#else
  #include "../core/LSingleBase.hpp"

  namespace lumina {
  namespace config {
    typedef LSingleBase CommonBase;
  }
  }

#endif
#undef USE_CONTEXT