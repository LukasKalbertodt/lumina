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

template <typename T, T Needle, T Head, T... Tail>
struct HeadInTail {
  static constexpr bool value = (Needle == Head)
                                | HeadInTail<T, Needle, Tail...>::value;
};

template <typename T, T Needle, T Head> 
struct HeadInTail<T, Needle, Head> {
  static constexpr bool value = (Needle == Head);
};

}