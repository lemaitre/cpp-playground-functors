#ifndef FUNCTORS_H
#define FUNCTORS_H

#include <utility>

namespace func {

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

template <typename F, typename... FS>
constexpr auto chain(F f, FS&&... fs) {
  auto ichain = chain(std::forward<FS>(fs)...);
  return Chainer<F, decltype(ichain)>{std::move(f), std::move(ichain)};
}

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

template <typename OP, typename F, typename... FS>
constexpr auto reduce(OP op, F f, FS&&... fs) {
  auto ired = reduce(op, std::forward<FS>(fs)...);
  return reduce(op, f, ired);
}

template <typename... FS>
constexpr auto add(FS&&... fs) {
  return reduce([](const auto& x, const auto& y) { return x + y; },
                std::forward<FS>(fs)...);
}

template <typename... FS>
constexpr auto mult(FS&&... fs) {
  return reduce([](const auto& x, const auto& y) { return x * y; },
                std::forward<FS>(fs)...);
}

};
#endif
