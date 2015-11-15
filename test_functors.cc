#include "functors.h"

#include <cmath>
#include <iostream>
#include <vector>

struct Point { double x, y; };

struct Track { std::vector<Point> points; };

struct Particle {
  double px, py, pz;
  Track t;
};

auto px(const Particle& p) { return p.px; }
auto py(const Particle& p) { return p.py; }
auto pz(const Particle& p) { return p.pz; }
auto track(const Particle& p) { return p.t; }
auto slope(const Track& t) {
  // Just a mock
  const auto first = t.points[0];
  const auto last = t.points[t.points.size() - 1];
  return (last.y - first.y) / (last.x - first.x);
}

int main() {
  auto particle = Particle{1.0, 2.0, 3.0, {{{0, 0}, {1, 1}, {2, 2}}}};

  auto square = [](const auto& x) { return x * x; };
  auto sqrt = [](const auto& x) { return std::sqrt(x); };
  auto fsquare = [square](auto f) { return func::chain(f, square); };

  auto sump2 = func::add(func::add(fsquare(px), fsquare(py)), fsquare(pz));
  auto p = func::chain(sump2, sqrt);

  std::cout << p(particle) << '\n';

  auto pslope = func::chain(track, slope);
  std::cout << pslope(particle) << '\n';
}
