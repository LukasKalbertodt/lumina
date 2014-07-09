#pragma once
/**
 * \file BaseProxy.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file is included by almost every file in the engine.
 * This file MUST define a class lumina::config::CommonBase 
 * (usually done by typedef), which implements a lumina base.
 * See L/core/LNullBase.hpp for more information.
 * In the default version of this file you can choose between two 
 * given implementations. See each file (L/core/LContextBase.hpp,
 * L/core/LSingleBase.hpp) for additional information about those 
 * implementations.
 * You can also use LNullBase as CommonBase, if you wish to disable some 
 * functionality.
 */
#define BASE_PROXY_USE_CONTEXT 1

// if the service context is used, there is one service for each context
#if BASE_PROXY_USE_CONTEXT
  #include "../core/ContextBase.hpp"

  namespace lumina {
  namespace config {
    typedef ContextBase CommonBase;
  }
  }

// if the service context is not used, every service is a singleton
#else
  #include "../core/SingleBase.hpp"

  namespace lumina {
  namespace config {
    typedef SingleBase CommonBase;
  }
  }

#endif
#undef BASE_PROXY_USE_CONTEXT