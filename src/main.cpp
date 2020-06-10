#include <cmath>
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
double HitSphere(const Point3& center, double radius, const Ray& ray)
{
  Vector3 oc = ray.Origin() - center;
  auto a = ray.Direction().LengthSquared();
  auto half_b = Vector3::Dot(oc, ray.Direction());
  auto c = Vector3::Dot(oc, oc) - radius * radius;
  auto discriminant =  half_b*half_b - a*c;

  if (discriminant < 0)
  {
    return -1;
  }
  else
  {
    return (-half_b - std::sqrt(discriminant)) / a;
  }
}

Color RayColor(const Ray& ray)
{
  auto sphere_center = Point3(0, 0, -1);
  auto t = HitSphere(sphere_center, 0.5, ray);

  if (t > 0)
  {
    // Calculate the normal, which is (P - C), normalized; each component may be in range [-1,1]
    auto normal = (ray.At(t) - sphere_center).Normalize();

    // Remap -1/1 to 0/1 by dividing between 2 (*0.5) and adding 1
    return 0.5 * (1 + normal);
  }

  t = 0.5 * (ray.Direction().Y() + 1.0);
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 384;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);

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
