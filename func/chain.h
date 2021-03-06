#ifndef CHAIN_H
#define CHAIN_H


#include <tuple>
#include <utility>
#include "invoke.h"
#include "is_callable.h"


// Forward chaining: (f >> g)(x) <=> g(f(x))
template <typename LHS, typename RHS,
  typename = typename std::enable_if<func::is_callable<LHS>::value && func::is_callable<RHS>::value>::type
>
constexpr auto operator>>(LHS lhs, RHS rhs) {
  return [lhs=std::forward<LHS>(lhs),rhs=std::forward<RHS>(rhs)](auto&&... args) { return rhs(lhs(std::forward<decltype((args))>(args)...)); };
  //return func::chain(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
}

// Backward chaining: (f << g)(x) <=> f(g(x))
template <typename LHS, typename RHS,
  typename = typename std::enable_if<func::is_callable<LHS>::value && func::is_callable<RHS>::value>::type
>
constexpr auto operator<<(LHS lhs, RHS rhs) {
  return [lhs=std::forward<LHS>(lhs),rhs=std::forward<RHS>(rhs)](auto&&... args) { return lhs(rhs(std::forward<decltype((args))>(args)...)); };
  //return func::chain(std::forward<RHS>(rhs), std::forward<LHS>(lhs));
}

namespace func {

  struct chain {
  private:
    template <typename F>
    static constexpr auto _call(F&& f) {
      return std::forward<F>(f);
    }
    template <typename HEAD, typename... TAIL>
    static constexpr auto _call(HEAD&& h, TAIL&&... tail) {
      return std::forward<HEAD>(h) >> _call(std::forward<TAIL>(tail)...);
      //return [=](auto&&... args) { return _call(tail...)(h(std::forward<decltype((args))>(args)...)); };
    }
  public:
    template <typename HEAD, typename... TAIL>
    constexpr auto operator()(HEAD&& h, TAIL&&... tail) const {
      return _call(std::forward<HEAD>(h), std::forward<TAIL>(tail)...);
    }
  } chain;
}

#endif  // CHAIN_H
