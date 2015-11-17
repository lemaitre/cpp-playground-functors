#ifndef ADD_H
#define ADD_H

#include "reduce.h"

#include <utility>

namespace func {

template <typename... FS>
constexpr auto add(FS&&... fs) {
  return reduce([](const auto& x, const auto& y) { return x + y; },
                std::forward<FS>(fs)...);
}
};

#endif  // ADD_H
