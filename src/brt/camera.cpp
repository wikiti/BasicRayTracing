#include <cmath>

#include "brt/camera.hpp"
#include "brt/utils.hpp"

namespace BRT
{
  Camera::Camera(Point3 look_from, Point3 look_at, Vector3 up, double aspect_ratio, double fov,
    double aperture) : origin(look_from)
  {
    auto theta = Utils::DegreesToRadians(fov);
    auto h = std::tan(theta / 2);

    auto viewport_height = 2.0 * h;
    auto viewport_width = viewport_height * aspect_ratio;
    auto focus_distance = (look_from - look_at).Length();

    w = (look_from - look_at).Normalize();
    u = Vector3::Cross(up, w).Normalize();
    v = Vector3::Cross(w, u);

    horizontal = focus_distance * viewport_width * u;
    vertical = focus_distance * viewport_height * v ;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_distance * w;

    lens_radius = aperture / 2;
  }

  Ray Camera::GetRay(double s, double t) const
  {
    Vector3 rd = lens_radius * Utils::RandomInUnitDisk();
    Vector3 offset = u * rd.X() + v * rd.Y();

    return Ray(
      origin + offset,
      lower_left_corner + s * horizontal + t * vertical - origin - offset
    );
  }
}
