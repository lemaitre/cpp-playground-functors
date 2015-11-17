#include "func/func.h"
#include "mock_particle.h"

#include <cmath>
#include <iostream>

int main() {
  auto particle = Particle{1.0, 2.0, 3.0, {{{0, 0}, {1, 1}, {2, 2}}}};

  auto square = [](const auto& x) { return x * x; };
  auto sqrt = [](const auto& x) { return std::sqrt(x); };

  auto fsquare = func::lift(square);
  auto fsqrt = func::lift(sqrt);

  auto p = fsqrt(func::add(func::map(fsquare, px, py, pz)));

  std::cout << p(particle) << '\n';

  auto pslope = func::chain(track, slope);
  std::cout << pslope(particle) << '\n';
}
