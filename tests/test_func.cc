
#include <cmath>
#include <iostream>
#include "mock_particle.h"
#include "func/func.h"

float sqrt2(float a) { return std::sqrt(a); }
auto test(const Particle& particle) {
  auto square = [](const auto& x) { return x * x; };
  auto sqrt = [](const auto& x) { return std::sqrt(x); };

  //auto p = func::map(square, px, py, pz) >> func::add >> sqrt;
  auto p = sqrt << func::add << func::map(square, px, py, pz);

  return p(particle);
}

int main() {
  auto particle = Particle{1.0, 2.0, 3.0, {{{0, 0}, {1, 1}, {2, 2}}}};

  std::cout << test(particle) << '\n';

  auto pslope = track >> slope;
  std::cout << pslope(particle) << '\n';
}
