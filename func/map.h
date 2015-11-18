#ifndef MAP_H
#define MAP_H

#include <tuple>
#include <utility>

namespace func {

  struct {
    template <typename F, typename... FS>
    constexpr auto operator()(F f, FS... fs) {
      return [=](auto... args) {
        return std::make_tuple(f(fs(args...))...);
      };
    }
  } map;
  // template <typename FN, typename... TS>
  // constexpr auto map(FN f, TS&&... ts) {
  //   return std::make_tuple(f(std::forward<TS>(ts))...);
  // }
}

#endif  // MAP_H
