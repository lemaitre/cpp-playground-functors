#ifndef MULT_H
#define MULT_H

#include "reduce.h"

#include <utility>

namespace func {

template <typename... FS>
constexpr auto mult(FS&&... fs) {
  return reduce([](const auto& x, const auto& y) { return x * y; },
                std::forward<FS>(fs)...);
}
};

#endif  // MULT_H
