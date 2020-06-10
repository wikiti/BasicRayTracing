#pragma once

#include "rtiow/point3.hpp"
#include "rtiow/ray.hpp"
#include "rtiow/vector3.hpp"

namespace RTIOW
{
  class Camera {
    public:

      Camera(Point3, double, double);

      Ray GetRay(double, double) const;

    private:

      Point3 origin;
      Point3 lower_left_corner;
      Vector3 horizontal;
      Vector3 vertical;
  };
}
