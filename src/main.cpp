#include "rtiow.hpp"

using RTIOW::Camera;
using RTIOW::Color;
using RTIOW::HitInfo;
using RTIOW::Hittable;
using RTIOW::HittableList;
using RTIOW::Utils;
using RTIOW::Point3;
using RTIOW::Progress;
using RTIOW::Ray;
using RTIOW::Sphere;
using RTIOW::Vector3;

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
  const int samples_per_pixel = 100;

  Camera camera(Vector3::Zero, aspect_ratio, 1.0);

  HittableList world;
  world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  std::cout << "P3" << std::endl;
  std::cout << image_width << ' ' << image_height << ' ' << std::endl;
  std::cout << "255" << std::endl;

  RTIOW::Progress progress(std::cerr, image_height - 1);

  for (int j = image_height - 1; j >= 0; --j)
  {
    progress.update(image_height - j - 1);

    for (int i = 0; i < image_width; ++i)
    {
      Color pixel_color;

      for (int k = 0; k < samples_per_pixel; ++k)
      {
        auto u = (i + Utils::Random()) / (image_width - 1);
        auto v = (j + Utils::Random()) / (image_height - 1);
        Ray ray = camera.GetRay(u, v);
        pixel_color += RayColor(ray, world);
      }

      Color average_color = pixel_color / samples_per_pixel;
      std::cout << average_color << std::endl;
    }
  }

  return 0;
}
