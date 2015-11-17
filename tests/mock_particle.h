#ifndef MOCK_PARTICLE_H
#define MOCK_PARTICLE_H

#include <vector>

struct Point {
  double x, y;
};

struct Track {
  std::vector<Point> points;
};

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

#endif  // MOCK_PARTICLE_H
