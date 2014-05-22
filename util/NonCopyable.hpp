#pragma once

namespace lumina {

class NonCopyable {
protected:
  NonCopyable() = default;

  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;
  NonCopyable(NonCopyable&&) = delete;
  NonCopyable& operator==(NonCopyable&&) = delete;
};

}