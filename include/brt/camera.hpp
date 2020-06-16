#pragma once

#include "brt/point3.hpp"
#include "brt/ray.hpp"
#include "brt/vector3.hpp"

namespace BRT
{
  class Camera {
    public:

      Camera(Point3 look_from, Point3 look_at, Vector3 up, double aspect_ratio, double fov,
        double aperture, double time_start = 0, double time_end = 0);

      Ray GetRay(double, double) const;

    private:

      Point3 origin;
      Point3 lower_left_corner;
      Vector3 horizontal;
      Vector3 vertical;
      Vector3 u, v, w;
      double lens_radius;
      double time_start, time_end; // Used in moving blur (shutter open/close times)
  };
}
