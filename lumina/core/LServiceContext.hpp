#pragma once

#include <cstdint>

namespace lumina {

enum class LServiceContext : uint8_t {
  DEFAULT,
  DEBUG,
  EXCONTEXT0,
  EXCONTEXT1,
  EXCONTEXT2,
  EXCONTEXT3,
  EXCONTEXT4,
  NUM_VALUES
};

} // namespace lumina
