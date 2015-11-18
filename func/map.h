#ifndef MAP_H
#define MAP_H

#include <tuple>
#include <utility>

namespace func {

  template <typename FN, typename... TS>
  constexpr auto map(FN f, TS&&... ts) {
    return std::make_tuple(f(std::forward<TS>(ts))...);
  }
}

#endif  // MAP_H
