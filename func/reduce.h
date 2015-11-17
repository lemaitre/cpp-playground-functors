#ifndef REDUCE_H
#define REDUCE_H

#include "invoke.h"

#include <tuple>
#include <utility>

namespace func {

template <typename OP, typename LHS, typename RHS>
struct Reducer {
  OP op_;
  LHS lhs_;
  RHS rhs_;

  Reducer(OP op, LHS lhs, RHS rhs)
      : op_{std::move(op)}, lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  template <typename T>
  auto operator()(T&& x) {
    return op_(lhs_(std::forward<T>(x)), rhs_(std::forward<T>(x)));
  }
};

template <typename OP, typename LHS, typename RHS>
constexpr auto reduce(OP op, LHS lhs, RHS rhs) {
  return Reducer<OP, LHS, RHS>{std::move(op), std::move(lhs), std::move(rhs)};
}

template <typename OP, typename... TS>
constexpr auto reduce(OP op, std::tuple<TS...>&& tup) {
  auto reduce_with_op = [=](auto... xs) { return reduce(op, xs...); };
  return invoke(reduce_with_op, std::move(tup));
}

template <typename OP, typename F, typename... FS>
constexpr auto reduce(OP op, F f, FS&&... fs) {
  auto ired = reduce(op, std::forward<FS>(fs)...);
  return reduce(op, f, ired);
}
};

#endif  // REDUCE_H
