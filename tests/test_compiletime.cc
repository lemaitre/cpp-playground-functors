#include "func/compiletime.h"

struct Doubler {
  template <typename T>
  static constexpr auto __call__(const T& x) {
    return 2 * x;
  }
};

struct Adder5 {
  template <typename T>
  static constexpr auto __call__(const T& x) {
    return 5 + x;
  }
};

int main() {
  auto fdoub = func::compiletime::Functor<Doubler>{};
  auto fadd5 = func::compiletime::Functor<Adder5>{};

  auto  f = fdoub + fadd5;

  return f(2);
}
