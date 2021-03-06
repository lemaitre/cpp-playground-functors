#ifndef WRAP_H
#define WRAP_H

namespace func {
  struct wrap {
  private:
    template <typename F, typename = void>
    struct _impl;

    template <typename F>
    struct _impl<F, typename std::enable_if<std::is_member_function_pointer<F>::value>::type> {
      static constexpr auto call(F&& f) {
        return [f=std::forward<F>(f)](auto&& o, auto&&... args) { return (std::forward<decltype((o))>(o).*f)(std::forward<decltype((args))>(args)...); };
      }
    };
    template <typename F>
    struct _impl<F, typename std::enable_if<!std::is_member_function_pointer<F>::value>::type> {
      static constexpr auto call(F&& f) {
        return [f=std::forward<F>(f)](auto&&... args) { return f(std::forward<decltype((args))>(args)...); };
      }
    };
  public:
    template <typename F>
    constexpr auto operator()(F&& f) const {
      return _impl<F>::call(std::forward<F>(f));
    }
  } wrap;
}

#endif
