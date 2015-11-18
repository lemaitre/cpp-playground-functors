#ifndef ADD_H
#define ADD_H

#include "reduce.h"

#include <utility>

namespace func {

  struct {
    template <typename... ARGS>
    constexpr auto operator()(ARGS&&... args) {
      return reduce(0, [](auto lhs, auto rhs) { return lhs + rhs; },
          std::forward<ARGS>(args)...
      );
    }
  } add;
  //auto fadd = func::lift(add);
// template <typename... FS>
// constexpr auto add(FS&&... fs) {
//   return reduce(0, [](const auto& x, const auto& y) { return x + y; },
//                 std::forward<FS>(fs)...);
// }
}

#endif  // ADD_H
