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

template <typename F, typename... FS>
constexpr auto add(F f, FS&&... fs) {
  auto iadd = add(std::forward<FS>(fs)...);
  return Adder<F, decltype(iadd)>{std::move(f), std::move(iadd)};
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

template <typename F, typename... FS>
constexpr auto mult(F f, FS&&... fs) {
  auto imult = mult(std::forward<FS>(fs)...);
  return Multiplier<F, decltype(imult)>{std::move(f), std::move(imult)};
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

template <typename F, typename... FS>
constexpr auto chain(F f, FS&&... fs) {
  auto ichain = chain(std::forward<FS>(fs)...);
  return Chainer<F, decltype(ichain)>{std::move(f), std::move(ichain)};
}

template <typename F>
struct Applier {
  F f_;

  explicit Applier(F f) : f_{std::move(f)} {}

  template <typename RHS>
  auto operator()(RHS&& rhs) {
    return chain(std::forward<RHS>(rhs), f_);
  }
};

template <typename F>
constexpr auto apply(F f) {
  return Applier<F>{std::move(f)};
}

};
#endif
