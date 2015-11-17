#ifndef CHAIN_H
#define CHAIN_H

#include "invoke.h"

#include <tuple>
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

template <typename... TS>
constexpr auto chain(std::tuple<TS...>&& tup) {
  return invoke(chain, std::move(tup));
}
};

#endif  // CHAIN_H
