
#include <cmath>
#include <iostream>
#include "mock_particle.h"
#include "func/func.h"

#define fwrap(...) ([=](auto... args){return __VA_ARGS__(args...);})
auto test(float x, float y) {
  return func::add(x, y);
}
auto test(float x, float y, float z) {
  return func::add(x, y, z);
}

auto doubler(float a) {
  return 2*a;
}

float square(float x) { return x*x; }
float sqrt2(float x) { return std::sqrt(x); }

auto abs(float a) {
  auto d = [](auto x){ return x*x;};
  //auto f = func::chaintest(sqrt2, square);
  auto f = fwrap(square) >> sqrt2;
  return f(a);
}

int main() {
  auto particle = Particle{1.0, 2.0, 3.0, {{{0, 0}, {1, 1}, {2, 2}}}};

  auto square = [](const auto& x) { return x * x; };
  auto sqrt = [](const auto& x) { return std::sqrt(x); };

  //auto fsquare = func::lift(square);
  //auto fsqrt = func::lift(sqrt);

  //auto p = fsqrt(func::fadd(func::map(fsquare, px, py, pz)));

  auto abs = doubler >> square;

  //std::cout << p(particle) << '\n';
  std::cout << func::add(1) << std::endl;
  std::cout << func::add(std::make_tuple()) << std::endl;
  std::cout << abs(5) << std::endl;
  std::cout << abs(-5) << std::endl;

  auto pslope = func::chain(track, slope);
  std::cout << pslope(particle) << '\n';
}
