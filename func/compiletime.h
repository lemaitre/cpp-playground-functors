#ifndef COMPILETIME_H
#define COMPILETIME_H

#include <utility>

namespace func {
namespace compiletime {

template <typename FN>
struct Lifter {
  // Problem is for most functions you actually need an instance of a function
  // object here which sucks.
};


template <typename LHS, typename RHS>
struct Adder {
  template <typename... ARGS>
  static constexpr auto __call__(ARGS&&... args) {
    return LHS::__call__(std::forward<ARGS>(args)...) +
           RHS::__call__(std::forward<ARGS>(args)...);
  }
};


template <typename F>
struct Functor {
  template <typename... ARGS>
  auto operator()(ARGS&&... args) const {
    return F::__call__(std::forward<ARGS>(args)...);
  }

  template <typename RHS>
  auto operator+(Functor<RHS>) const {
    return Functor<Adder<F, RHS>>{};
  }
};

};
};

#endif  // COMPILETIME_H
