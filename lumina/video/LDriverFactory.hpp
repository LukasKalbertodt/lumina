#pragma once

#include "LDriverTraits.hpp"
#include "LDriverType.hpp"

#include <memory>
#include <stdexcept>

namespace lumina {

class LDriverFactory {
public:
  LDriverFactory(LDriverType type)
    : m_type(type) {
  }

  template <typename T, typename... Args>
  std::shared_ptr<T> make(Args... args) {
    switch(m_type) {
      case LDriverType::OpenGL:
        return std::make_shared<typename LDriverTraits<T>::GLType>(args...);

      // case LDriverType::DirectX:
      //   return std::make_shared<typename LDriverTraits<T>::DXType>(args...);
    }
    throw std::runtime_error("Internal: Invalid Driver type in Factory");
  }

private:
  LDriverType m_type;
};

} // namespace lumina