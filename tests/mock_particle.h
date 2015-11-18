#ifndef MOCK_PARTICLE_H
#define MOCK_PARTICLE_H

#include "func/wrap.h"
#include <vector>

struct Point {
  double x, y;
};

struct Track {
  std::vector<Point> points;
};

struct Particle {
  double _px, _py, _pz;
  Track t;

  auto px() const { return _px; }
  auto py() const { return _py; }
  auto pz() const { return _pz; }
  auto track() const { return t; }
};

//auto px = func::wrap(&Particle::px);
//auto py = func::wrap(&Particle::py);
//auto pz = func::wrap(&Particle::pz);
//auto track = func::wrap(&Particle::track);

auto px(const Particle& p) { return p._px; }
auto py(const Particle& p) { return p._py; }
auto pz(const Particle& p) { return p._pz; }
auto track(const Particle& p) { return p.t; }
auto slope(const Track& t) {
  // Just a mock
  const auto first = t.points[0];
  const auto last = t.points[t.points.size() - 1];
  return (last.y - first.y) / (last.x - first.x);
}

#endif  // MOCK_PARTICLE_H
