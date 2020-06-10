#include "rtiow.hpp"

using RayTracingInOneWeekend::Color;
using RayTracingInOneWeekend::HitInfo;
using RayTracingInOneWeekend::Hittable;
using RayTracingInOneWeekend::HittableList;
using RayTracingInOneWeekend::Utils;
using RayTracingInOneWeekend::Point3;
using RayTracingInOneWeekend::Progress;
using RayTracingInOneWeekend::Ray;
using RayTracingInOneWeekend::Sphere;
using RayTracingInOneWeekend::Vector3;

Color RayColor(const Ray& ray, const Hittable& world)
{
  HitInfo hit_info;

  if (world.Hit(ray, 0, Utils::Infinity, hit_info))
  {
    return 0.5 * (hit_info.normal + Color(1, 1, 1));
  }

  auto t = 0.5 * (ray.Direction().Y() + 1.0);
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

  HittableList world;
  world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

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
      Color color = RayColor(ray, world);

      std::cout << color << std::endl;
    }
  }

  return 0;
}
