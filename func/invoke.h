#ifndef INVOKE_H
#define INVOKE_H

#include <tuple>
#include <utility>

namespace func {

  template <typename FN, typename TUP, std::size_t... index>
  auto invoke_helper(FN&& f, TUP&& tup, std::index_sequence<index...>) {
    return f(std::get<index>(std::forward<TUP>(tup))...);
  }

  template <typename FN, typename TUP>
  auto invoke(FN&& f, TUP&& tup) {
    constexpr auto Size = std::tuple_size<std::decay_t<TUP>>::value;
    return invoke_helper(std::forward<FN>(f), std::forward<TUP>(tup),
                         std::make_index_sequence<Size>{});
  }
}

#endif  // INVOKE_H
