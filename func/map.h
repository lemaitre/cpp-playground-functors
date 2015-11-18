#ifndef MAP_H
#define MAP_H

#include <tuple>
#include <utility>

namespace func {

  struct map {
    template <typename F, typename... FS>
    constexpr auto operator()(F f, FS... fs) const {
      return [=](auto&&... args) {
        return std::make_tuple(f(fs(std::forward<decltype((args))>(args)...))...);
      };
    }
  } map;
}

#endif  // MAP_H
