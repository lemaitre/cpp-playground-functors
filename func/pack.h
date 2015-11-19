#ifndef PACK_H
#define PACK_H

#include <tuple>

namespace func {
  struct pack {
    template <typename... ARGS>
    constexpr auto operator()(ARGS&&... args) const {
      return std::make_tuple(std::forward<ARGS>(args)...);
    }
  } pack;
}

#endif // PACK_H
