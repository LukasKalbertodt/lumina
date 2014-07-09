#pragma once

#include <cstdint>

namespace lumina {

using LogLevelBaseType = uint8_t;

enum class LogLevel : LogLevelBaseType {
  Critical,
  Error,
  Warning,
  Notice,
  Info,
  Debug
};

inline bool operator<(LogLevel a, LogLevel b) {
  return static_cast<LogLevelBaseType>(a) > static_cast<LogLevelBaseType>(b);
}
inline bool operator>(LogLevel a, LogLevel b) {
  return static_cast<LogLevelBaseType>(a) < static_cast<LogLevelBaseType>(b);
}
inline bool operator<=(LogLevel a, LogLevel b) {
  return static_cast<LogLevelBaseType>(a) >= static_cast<LogLevelBaseType>(b);
}
inline bool operator>=(LogLevel a, LogLevel b) {
  return static_cast<LogLevelBaseType>(a) <= static_cast<LogLevelBaseType>(b);
}


template <LogLevel LL> struct LogLevelTrait;

#define XLogLevelTraits(level_, string_)                                       \
  template <> struct LogLevelTrait<LogLevel::level_> {                         \
    static constexpr char const* string = string_;                             \
  };

XLogLevelTraits(Critical, "CRIT")
XLogLevelTraits(Error, "ERROR")
XLogLevelTraits(Warning, "WARN")
XLogLevelTraits(Notice, "NOTE")
XLogLevelTraits(Info, "INFO")
XLogLevelTraits(Debug, "DEBUG")

#undef XLogLevelTraits


}