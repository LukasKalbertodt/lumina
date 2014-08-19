#pragma once

#include <chrono>


namespace lumina {

class Timer {
public:
  void start() {
    m_start = std::chrono::system_clock::now();
  }

  template <typename T = float>
  T getTime() {
    auto diff = chrono::system_clock::now() - m_start;
    float s = chrono::duration_cast<std::chrono::microseconds>(diff).count()
              / 10000000.f;
    return s;
  }

private:
  std::chrono::system_clock::time_point m_start;

};


}