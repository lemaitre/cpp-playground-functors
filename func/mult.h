#ifndef MULT_H
#define MULT_H

#include "reduce.h"

#include <utility>

namespace func {

  struct mult {
    template <typename... ARGS>
    constexpr auto operator()(ARGS&&... args) const {
      return reduce(1, [](auto&& lhs, auto&& rhs) { return lhs * rhs; },
          std::forward<ARGS>(args)...
      );
    }
  } mult;
}

#endif  // MULT_H
