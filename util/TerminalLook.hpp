#pragma once
/**
 * \file TerminalLook.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file defines functions for manipulating the appearance of the terminal 
 * (std::cout). Works for Windows and compatible linux terminals.
 */
#include <ostream>

#ifdef _WIN32
  #include <Windows.h>
#endif

namespace lumina {


enum class TerminalLook {
  // control
  Reset,        // reset all formats and colors
  ResetText,    // reset text color
  ResetBG,      // reset background color
  ResetWeight,  // reset font weight
  ResetDec,     // reset decoration

  // font weight
  Bold,   // bolder font
  Thin,   // thinner font

  // decoration
  Underline,  // underlined

  // text color
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White,

  // background color
  BlackBG,
  RedBG,
  GreenBG,
  YellowBG,
  BlueBG,
  MagentaBG, 
  CyanBG,
  WhiteBG,
};

// short typedef
using TL = TerminalLook;

/**
 * @brief Overloaded operator<< for applying TL values
 * 
 * @param out cout-stream (do not use with another ostream!)
 * @param look TL code to apply
 */
inline std::ostream& operator<<(std::ostream& out, TL look) {

#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          (csbi.wAttributes & 0xFFF0)
                          | static_cast<int>(color));


#else
  // output special ANSI escape code, for more information:
  // http://en.wikipedia.org/wiki/ANSI_escape_code#graphics
  switch(look) {
    case TL::Reset:       out << "\033[0m"; break;
    case TL::ResetText:   out << "\033[39m"; break;
    case TL::ResetBG:     out << "\033[49m"; break;
    case TL::ResetWeight: out << "\033[22m"; break;
    case TL::ResetDec:    out << "\033[24m"; break;
    case TL::Bold:        out << "\033[1m"; break;
    case TL::Thin:        out << "\033[2m"; break;
    case TL::Underline:   out << "\033[4m"; break;
    case TL::Black:       out << "\033[30m"; break;
    case TL::Red:         out << "\033[31m"; break;
    case TL::Green:       out << "\033[32m"; break;
    case TL::Yellow:      out << "\033[33m"; break;
    case TL::Blue:        out << "\033[34m"; break;
    case TL::Magenta:     out << "\033[35m"; break;
    case TL::Cyan:        out << "\033[36m"; break;
    case TL::White:       out << "\033[37m"; break;
    case TL::BlackBG:     out << "\033[40m"; break;
    case TL::RedBG:       out << "\033[41m"; break;
    case TL::GreenBG:     out << "\033[42m"; break;
    case TL::YellowBG:    out << "\033[43m"; break;
    case TL::BlueBG:      out << "\033[44m"; break;
    case TL::MagentaBG:   out << "\033[45m"; break;
    case TL::CyanBG:      out << "\033[46m"; break;
    case TL::WhiteBG:     out << "\033[47m"; break;
  }
#endif

  return out;
}

} // namespace lumina