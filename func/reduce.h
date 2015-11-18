#ifndef REDUCE_H
#define REDUCE_H

#include "invoke.h"

#include <tuple>
#include <utility>

namespace func {

  struct {
  private:
    // Helper to detect tuples
    template <typename T>
    struct is_tuple {
      typedef void disable;
    };
    template <typename... ARGS>
    struct is_tuple<std::tuple<ARGS...>> {
      typedef void enable;
    };
    // Helper to recursively reduce
    template <typename T, typename OP, typename dummy, typename... ARGS>
    struct _impl;
    template <typename T, typename OP, typename dummy>
    struct _impl<T, OP, dummy> {
      static constexpr auto call(T t, OP op) {
        return std::forward<T>(t);
      }
    };
    template <typename T, typename OP, typename HEAD>
    struct _impl<T, OP, typename is_tuple<HEAD>::disable, HEAD> {
      static constexpr auto call(T t, OP op, HEAD h) {
        return std::forward<HEAD>(h);
      }
    };
    template <typename T, typename OP, typename HEAD, typename... TAIL>
    struct _impl<T, OP, typename is_tuple<HEAD>::disable, HEAD, TAIL...> {
      static constexpr auto call(T t, OP op, HEAD h, TAIL&&... tail) {
        return op(std::forward<HEAD>(h), _impl<T, OP, void, TAIL...>::call(std::forward<T>(t), std::forward<OP>(op), std::forward<TAIL>(tail)...));
      }
    };
    template <typename T, typename OP, typename dummy, typename... ARGS>
    struct _impl<T, OP, dummy, std::tuple<ARGS...>> {
      static constexpr auto call(T t, OP op, std::tuple<ARGS...>&& tup) {
        return invoke([&t, &op](auto... args){return _call(t, op, args...);}, tup);
      }
    };
    // Helper to call _impl<...>::call() inside the lambda
    template <typename T, typename OP, typename... ARGS>
    static constexpr auto _call(T t, OP op, ARGS&&... args) {
      return _impl<T, OP, void, ARGS...>::call(std::forward<T>(t), std::forward<OP>(op), std::forward<ARGS>(args)...);
    }
  public:
    // actual interface
    template <typename T, typename OP, typename... ARGS>
    constexpr auto operator()(T t, OP op, ARGS&&... args) const {
      return _call(std::forward<T>(t), std::forward<OP>(op), std::forward<ARGS>(args)...);
    }
  } reduce;
}

#endif  // REDUCE_H
