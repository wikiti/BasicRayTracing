#pragma once

#include "rtiow/point3.hpp"
#include "rtiow/ray.hpp"
#include "rtiow/vector3.hpp"

namespace RTIOW
{
  class Camera {
    public:

      Camera(Point3 look_from, Point3 look_at, Vector3 up, double aspect_ratio, double fov,
        double aperture);

      Ray GetRay(double, double) const;

    private:

      Point3 origin;
      Point3 lower_left_corner;
      Vector3 horizontal;
      Vector3 vertical;
      Vector3 u, v, w;
      double lens_radius;
  };
}
