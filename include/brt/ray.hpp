#pragma once

#include "brt/point3.hpp"
#include "brt/vector3.hpp"

namespace BRT
{
  class Ray
  {
    public:

      Ray();
      Ray(const Point3&, const Vector3&, double = 0.0);

      Point3 Origin() const;
      Vector3 Direction() const;
      double Time() const;

      Point3 At(double) const;

    private:

      Point3 origin;
      Vector3 direction;
      double time;
  };
}
