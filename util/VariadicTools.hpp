#pragma once

namespace lumina {

template <typename T, typename... Ts> 
struct VariadicTools {
  using first = T;
  using last = VariadicTools<Ts...>;
};

template <typename T>
struct VariadicTools<T> {
  using first = T;
  using last = T;
};

}