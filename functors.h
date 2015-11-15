#ifndef FUNCTORS_H
#define FUNCTORS_H

#include <utility>

namespace func {

template <typename LHS, typename RHS>
struct Adder {
  LHS lhs_;
  RHS rhs_;

  Adder(LHS lhs, RHS rhs) : lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  template <typename T>
  auto operator()(T&& x) {
    return lhs_(std::forward<T>(x)) + rhs_(std::forward<T>(x));
  }
};

template <typename LHS, typename RHS>
constexpr auto add(LHS lhs, RHS rhs) {
  return Adder<LHS, RHS>{std::move(lhs), std::move(rhs)};
}

template <typename LHS, typename RHS>
struct Multiplier {
  LHS lhs_;
  RHS rhs_;

  Multiplier(LHS lhs, RHS rhs) : lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  template <typename T>
  auto operator()(T&& x) {
    return lhs_(std::forward<T>(x)) + rhs_(std::forward<T>(x));
  }
};

template <typename LHS, typename RHS>
constexpr auto mult(LHS lhs, RHS rhs) {
  return Multiplier<LHS, RHS>{std::move(lhs), std::move(rhs)};
}

template <typename LHS, typename RHS>
struct Chainer {
  LHS lhs_;
  RHS rhs_;

  Chainer(LHS lhs, RHS rhs) : lhs_{std::move(lhs)}, rhs_{std::move(rhs)} {}

  template <typename T>
  auto operator()(T&& x) {
    return rhs_(lhs_(std::forward<T>(x)));
  }
};

template <typename LHS, typename RHS>
constexpr auto chain(LHS lhs, RHS rhs) {
  return Chainer<LHS, RHS>{std::move(lhs), std::move(rhs)};
}
};

#endif
