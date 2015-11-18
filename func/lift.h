#ifndef LIFT_H
#define LIFT_H

#include "chain.h"

#include <utility>

namespace func {

  template <typename F>
  struct Lifter {
    F f_;

    explicit Lifter(F f) : f_{std::move(f)} {}

    template <typename RHS>
    auto operator()(RHS&& rhs) {
      return chain(std::forward<RHS>(rhs), f_);
    }
  };

  template <typename F>
  constexpr auto lift(F f) {
    return Lifter<F>{std::move(f)};
  }
}

#endif  // LIFT_H
