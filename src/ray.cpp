#include "ray.hpp"

namespace RayTracingInOneWeekend
{
  Ray::Ray()
  {}

  Ray::Ray(const Point3& origin, const Vector3& direction) : origin(origin), direction(direction)
  {}

  Point3 Ray::Origin() const
  {
    return origin;
  }

  Vector3 Ray::Direction() const
  {
    return direction;
  }

  Point3 Ray::At(double t) const
  {
    return (Vector3)origin + t * direction;
  }
}
