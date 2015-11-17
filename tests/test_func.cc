#include "func/func.h"
#include "mock_particle.h"

#include <cmath>
#include <iostream>

auto test(float x, float y) {
  return func::add(x, y);
}
auto test(float x, float y, float z) {
  return func::add(x, y, z);
}

int main() {
  auto particle = Particle{1.0, 2.0, 3.0, {{{0, 0}, {1, 1}, {2, 2}}}};

  //auto square = [](const auto& x) { return x * x; };
  //auto sqrt = [](const auto& x) { return std::sqrt(x); };

  //auto fsquare = func::lift(square);
  //auto fsqrt = func::lift(sqrt);

  //auto p = fsqrt(func::fadd(func::map(fsquare, px, py, pz)));

  

  //std::cout << p(particle) << '\n';
  std::cout << func::add(1) << std::endl;
  std::cout << func::add(std::make_tuple()) << std::endl;

  auto pslope = func::chain(track, slope);
  std::cout << pslope(particle) << '\n';
}
