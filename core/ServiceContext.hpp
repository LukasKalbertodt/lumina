#pragma once

#include <cstdint>

namespace lumina {

enum class ServiceContext : uint8_t {
  Default,
  Static,
  Debug,
  ExContext0,
  ExContext1,
  ExContext2,
  ExContext3,
  ExContext4,
  NUM_VALUES
};

} // namespace lumina
