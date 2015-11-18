#ifndef IS_CALLABLE_H
#define IS_CALLABLE_H


namespace func {
  template<typename TYPE>
  struct is_callable {
  private:
    // Default: not callable
    template <class T, class = void>
    struct _impl {
      static const bool value = false;
    };
    // Plain functions are callable
    template <typename RET_TYPE, typename dummy, typename... ARGS>
    struct _impl<RET_TYPE(ARGS...), dummy> {
      static const bool value = true;
    };
    // Plain pointers to function are callable
    template <typename RET_TYPE, typename dummy, typename... ARGS>
    struct _impl<RET_TYPE(*)(ARGS...), dummy> {
      static const bool value = true;
    };
    // Classes: check the presence of operator()
    template <typename T>
    struct _impl<T, typename std::enable_if<std::is_class<T>::value>::type> {
      typedef char(&yes)[1];
      typedef char(&no)[2];

      struct Fallback { void operator()(); };
      struct Derived : T, Fallback { };

      template<typename U, U> struct Check;

      template<typename>
      static yes test(...);

      template<typename C>
      static no test(Check<void (Fallback::*)(), &C::operator()>*);
      static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
    };
  public:
    static const bool value = _impl<TYPE>::value;
  };
}

#endif
