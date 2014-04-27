#pragma once

#ifdef _WIN32
  #include "LWinWindow.hpp"
  namespace lumina {
    typedef LWinWindow LWindow;
  }
#else 
  #include "LUnixWindow.hpp"
  namespace lumina {
    typedef LUnixWindow LWindow;
  }
#endif