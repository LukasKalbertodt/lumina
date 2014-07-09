#pragma once

#include <sstream>
#include <stdexcept>

namespace lumina {

class LuminaException : public std::exception {
public:
  template <typename... Ts>  LuminaException(Ts...);
  LuminaException(const LuminaException& copy);
  const char* what() const noexcept;

private:
  std::stringstream m_what;

  template <typename T, typename... Ts>  void append(T, Ts...);
  template <typename T>  void append(T);
};


#define X(name_, base_)\
  class name_ : public base_ {\
    using base_::base_;\
  };

X(NotReadyEx, LuminaException)
X(LogicEx, LuminaException)
X(InvalidArgEx, LuminaException)
X(CriticalEx, LuminaException)
X(IOEx, LuminaException)
X(OutOfRangeEx, LuminaException)

#undef X

} // namespace lumina

#include "LuminaException.tpp"