#ifndef ADD_H
#define ADD_H

#include "reduce.h"

#include <utility>

namespace func {

  struct add {
    template <typename... ARGS>
    constexpr auto operator()(ARGS&&... args) const {
      return reduce(0, [](auto&& lhs, auto&& rhs) { return lhs + rhs; },
          std::forward<ARGS>(args)...
      );
    }
  } add;
}

#endif  // ADD_H
