#ifndef MULT_H
#define MULT_H

#include "reduce.h"

#include <utility>

namespace func {

  struct {
    template <typename... ARGS>
    constexpr auto operator()(ARGS&&... args) {
      return reduce(1, [](auto lhs, auto rhs) { return lhs * rhs; },
          std::forward<ARGS>(args)...
      );
    }
  } mult;
  //auto fmult = func::lift(mult);
//template <typename... FS>
//constexpr auto mult(FS&&... fs) {
//  return reduce([](const auto& x, const auto& y) { return x * y; },
//                std::forward<FS>(fs)...);
//}
}

#endif  // MULT_H
