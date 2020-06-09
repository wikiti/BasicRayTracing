#include <iostream>

#include "color.hpp"
#include "point3.hpp"
#include "progress.hpp"
#include "ray.hpp"
#include "vector3.hpp"

using RayTracingInOneWeekend::Color;
using RayTracingInOneWeekend::Point3;
using RayTracingInOneWeekend::Progress;
using RayTracingInOneWeekend::Ray;
using RayTracingInOneWeekend::Vector3;

Color RayColor(const Ray& r)
{
  Vector3 unit = r.Direction();

  auto t = 0.5 * (unit.Y() + 1.0);
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 384;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * aspect_ratio;
  auto focal_length = 1.0;

  auto origin = Point3(0, 0, 0);
  auto horizontal = Vector3(viewport_width, 0, 0);
  auto vertical = Vector3(0, viewport_height, 0);
  auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vector3(0, 0, focal_length);

  std::cout << "P3" << std::endl;
  std::cout << image_width << ' ' << image_height << ' ' << std::endl;
  std::cout << "255" << std::endl;

  RayTracingInOneWeekend::Progress progress(std::cerr, image_height - 1);

  for (int j = image_height - 1; j >= 0; --j)
  {
    progress.update(image_height - j - 1);

    for (int i = 0; i < image_width; ++i)
    {
      auto u = double(i) / (image_width - 1);
      auto v = double(j) / (image_height - 1);

      Ray ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
      Color color = RayColor(ray);

      std::cout << color << std::endl;
    }
  }

  return 0;
}
