#include "rtiow.hpp"

using RTIOW::Camera;
using RTIOW::Color;
using RTIOW::HitInfo;
using RTIOW::Hittable;
using RTIOW::HittableList;
using RTIOW::Materials::Dielectric;
using RTIOW::Materials::Lambertian;
using RTIOW::Materials::Metal;
using RTIOW::Utils;
using RTIOW::Point3;
using RTIOW::Progress;
using RTIOW::Ray;
using RTIOW::Sphere;
using RTIOW::Vector3;

Color RayColor(const Ray& ray, const Hittable& world, int depth)
{
  if (depth <= 0)
  {
    return Color(0, 0, 0);
  }

  HitInfo hit_info;

  // TODO: Overload Hit method to accept 2 arguments
  if (world.Hit(ray, 0.001, Utils::Infinity, hit_info))
  {
    Ray scattered;
    Color attenuation;

    if (hit_info.material_ptr->Scatter(ray, hit_info, attenuation, scattered))
    {
      return attenuation * RayColor(scattered, world, depth - 1);
    }

    return Color(0, 0, 0);
  }

  auto t = 0.5 * (ray.Direction().Y() + 1.0);
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

HittableList BuildWorld()
{
  HittableList world;
  world.Add(std::make_shared<Sphere>(
    Point3(0, 0, -1),
    0.5,
    std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5)))
  );
  world.Add(std::make_shared<Sphere>(
    Point3(0, -100.5, -1),
    100,
    std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0)))
  );

  world.Add(std::make_shared<Sphere>(
    Point3(1, 0, -1),
    0.5,
    std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0))
  );

  world.Add(std::make_shared<Sphere>(
    Point3(-1, 0, -1),
    0.5,
    std::make_shared<Dielectric>(1.5))
  );

  // Glass buble trick achieve by using a negative radius!
  world.Add(std::make_shared<Sphere>(
    Point3(-1, 0, -1),
    -0.45,
    std::make_shared<Dielectric>(1.5))
  );

  return world;
}

int main()
{
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 384;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  Camera camera(Point3(3, 3, 2), Point3(0, 0, -1), Vector3::Up, aspect_ratio, 20, 2.0);

  HittableList world = BuildWorld();

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
        pixel_color += RayColor(ray, world, max_depth);
      }

      Color average_color = pixel_color / samples_per_pixel;
      std::cout << average_color << std::endl;
    }
  }

  return 0;
}
