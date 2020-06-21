#include "brt/moving_point3.hpp"

namespace BRT {
  MovingPoint3::MovingPoint3(const Point3& from, const Point3& to,
    double time_start, double time_end) : from(from), to(to),
                                          time_start(time_start), time_end(time_end)
  {}

  const Point3& MovingPoint3::From() const
  {
    return from;
  }

  const Point3& MovingPoint3::To() const
  {
    return to;
  }

  Point3 MovingPoint3::At(double time) const
  {
    return from + ((time - time_start) / (time_end - time_start)) * (from - to);
  }
}
