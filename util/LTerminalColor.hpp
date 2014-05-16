#pragma once
/**
 * \file LTerminalColor.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file defines functions for manipulating the color of the terminal 
 * (std::cout). Works for Windows and compatible linux terminals.
 */
#include <ostream>

namespace lumina {

// LTerminalForeGround
enum class LTFG {
  Black   = 0,
  Red     = 1,
  Green   = 2,
  Yellow  = 3,
  Blue    = 4,
  Magenta = 5,
  Cyan    = 6,
  Gray    = 7
};

// LTerminalBackGround
enum class LTBG {
  Black   = 0,
  Red     = 1,
  Green   = 2,
  Yellow  = 3,
  Blue    = 4,
  Magenta = 5,
  Cyan    = 6,
  Gray    = 7
};

// special values to reset colours
enum LTC {
  Reset,
  ResetFG,
  ResetBG
};


// manipulate foreground colour with cout
inline std::ostream& operator<<(std::ostream& out, LTFG color) {
#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          (csbi.wAttributes & 0xFFF0) | c.GetWinForeground());
#else
  char code[] = "\033[1;30m";
  code[5] = static_cast<char>(color) + '0';
  out << code;
#endif
  return out;
}

// manipulate background colour with cout
inline std::ostream& operator<<(std::ostream& out, LTBG color) {
#ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                          (csbi.wAttributes & 0xFF0F) | c.GetWinBackground());
#else
  char code[] = "\033[40m";
  code[3] = static_cast<char>(color) + '0';
  out << code;
#endif
  return out;
}

// manipulate colour with special values
inline std::ostream& operator<<(std::ostream& out, const LTC control) {
#ifdef _WIN32
  switch(control) {
    case LTC::Reset:
      out << FG_WHITE;
      out << BG_BLACK;
      break;
    case LTC::ResetFG:
      out << FG_WHITE;
      break;
    case LTC::ResetBG:
      out << BG_BLACK;
      break;
  }
#else
  switch(control) {
    case LTC::Reset:
      out << "\033[0m";
      break;
    case LTC::ResetFG:
      out << "\033[22;39m";
      break;
    case LTC::ResetBG:
      out << "\033[49m";
      break;
  }
#endif
  return out;
}

} // namespace lumina