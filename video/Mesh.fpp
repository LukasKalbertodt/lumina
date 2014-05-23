#pragma once

namespace lumina {

class Mesh;
template <typename...> class HotMesh;

namespace internal {
  template <typename T, typename... Ts> struct AssignBufferWriter;
  template <typename... Cs> struct VBufferWriteHelper;
  template <typename T, typename... Ts> struct CommaBufferWriter;
}

}