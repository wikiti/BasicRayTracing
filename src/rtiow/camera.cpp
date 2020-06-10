#include "rtiow/camera.hpp"

#include <iostream>

namespace RTIOW
{
  Camera::Camera(Point3 o, double aspect_ratio, double focal_length) : origin(o)
  {
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;

    horizontal = Vector3(viewport_width, 0, 0);
    vertical = Vector3(0, viewport_height, 0);
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vector3(0, 0, focal_length);
  }

  Ray Camera::GetRay(double u, double v) const
  {
    return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
  }
}
