#include "brt/ray.hpp"

namespace BRT
{
  Ray::Ray()
  {}

  Ray::Ray(const Point3& origin, const Vector3& direction, double time) :
    origin(origin), direction(direction), time(time)
  {}

  Point3 Ray::Origin() const
  {
    return origin;
  }

  Vector3 Ray::Direction() const
  {
    return direction;
  }

  double Ray::Time() const
  {
    return time;
  }

  Point3 Ray::At(double t) const
  {
    return (Vector3)origin + t * direction;
  }
}
