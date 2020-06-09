#pragma once

#include "point3.hpp"
#include "vector3.hpp"

namespace RayTracingInOneWeekend
{
  class Ray
  {
    public:

      Ray();
      Ray(const Point3&, const Vector3&);

      Point3 Origin() const;
      Vector3 Direction() const;

      Point3 at(double) const;

    private:

      Point3 origin;
      Vector3 direction;
  };
}
