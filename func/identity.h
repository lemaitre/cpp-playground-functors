#ifndef IDENTITY_H
#define IDENTITY_H

#include "pack.h"

namespace func {
  struct identity {
    constexpr void operator()() const {}
    template <typename T>
    constexpr auto operator()(T&& t) const {
      return std::forward<T>(t);
    }
    template <typename T1, typename T2,typename... TS>
    constexpr auto operator()(T1&& t1, T2&& t2, TS&&... ts) const {
      return pack(std::forward<T1>(t1), std::forward<T2>(t2), std::forward<TS>(ts)...);
    }
  } identity;
}

#endif // IDENTITY_H
