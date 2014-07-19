#pragma once

namespace lumina {

struct LogicalAnd {
  static constexpr bool combine(bool a, bool b) { return a && b; } 
};

struct LogicalOr {
  static constexpr bool combine(bool a, bool b) { return a || b; } 
};

template <typename T, typename... Ts> 
struct VariadicTools {
  using first = T;
  using last = VariadicTools<Ts...>;

  template <typename LogicFunc, template <typename> class ValueFunc>
  static constexpr bool valueUnaryForEach() {
    return LogicFunc::combine(
      ValueFunc<T>::value,
      VariadicTools<Ts...>::template valueUnaryForEach<LogicFunc, ValueFunc>());
  }

  template <typename LogicFunc,
            template <typename, typename> class ValueFunc,
            typename U>
  static constexpr bool valueBinaryForEach() {
    return LogicFunc::combine(
      ValueFunc<T, U>::value,
      VariadicTools<Ts...>::template valueBinaryForEach<LogicFunc,
                                                        ValueFunc,
                                                        U>());
  }
};

template <typename T>
struct VariadicTools<T> {
  using first = T;
  using last = T;

  template <typename LogicFunc,
            template <typename> class ValueFunc,
            typename... Vs>
  static constexpr bool valueUnaryForEach() {
    return ValueFunc<T>::value;
  }
  template <typename LogicFunc,
            template <typename, typename> class ValueFunc,
            typename U>
  static constexpr bool valueBinaryForEach() {
    return ValueFunc<T, U>::value;
  }
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