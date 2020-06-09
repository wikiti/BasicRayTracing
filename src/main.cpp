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

/**
 * Point: P(x,y,z), Center: C(Cx,Cy,Cz), Radius: R, Ray: Pr(t) = A + tB
 *
 * (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = R^2
 * (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = (P - C) · (P - C)
 * (P - C) · (P - C) = R^2
 * (Pr(t) - C) · (Pr(t) - C) = R^2
 * (A + tB - C) · (A + tB - C) = R^2
 * t^2(B·B) + 2tB ⋅ (A - C) + (A - C)·(A - C) - R^2 = 0
 * - a = (B·B)
 * - b = 2·(A - C)
 * - c = (A - C)·(A - C) - R^2
 */
bool HitSphere(const Point3& center, double radius, const Ray& ray)
{
  Vector3 oc = ray.Origin() - center;
  auto a = Vector3::Dot(ray.Direction(), ray.Direction());
  auto b = 2.0 * Vector3::Dot(oc, ray.Direction());
  auto c = Vector3::Dot(oc, oc) - radius * radius;
  auto discriminant =  b*b - 4*a*c;
  return discriminant > 0;
}

Color RayColor(const Ray& r)
{
  if (HitSphere(Point3(0, 0, -1), 0.5, r))
  {
    return Color(1, 0, 0);
  }

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
