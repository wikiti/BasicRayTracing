#include "brt.hpp"

using BRT::Camera;
using BRT::Color;
using BRT::HitInfo;
using BRT::Hittable;
using BRT::HittableList;
using BRT::Materials::Dielectric;
using BRT::Materials::Lambertian;
using BRT::Materials::Material;
using BRT::Materials::Metal;
using BRT::Utils;
using BRT::Point3;
using BRT::Progress;
using BRT::Ray;
using BRT::Sphere;
using BRT::Vector3;

Color RayColor(const Ray& ray, const Hittable& world, int depth)
{
  if (depth <= 0)
  {
    return Color(0, 0, 0);
  }

  HitInfo hit_info;

  if (world.Hit(ray, hit_info))
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

  auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
  world.Add(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

  for (int a = -11; a < 11; ++a)
  {
      for (int b = -11; b < 11; ++b)
      {
          auto choose_mat = Utils::Random();
          Point3 center(a + 0.9 * Utils::Random(), 0.2, b + 0.9 * Utils::Random());

          if ((center - Point3(4, 0.2, 0)).Length() > 0.9)
          {
              std::shared_ptr<Material> sphere_material;

              if (choose_mat < 0.8) // diffuse
              {
                auto albedo = Color::Random() * Color::Random();
                sphere_material = std::make_shared<Lambertian>(albedo);
              }
              else if (choose_mat < 0.95) // metal
              {
                auto albedo = Color::Random(0.5, 1);
                auto fuzz = Utils::Random(0, 0.5);
                sphere_material = std::make_shared<Metal>(albedo, fuzz);
              }
              else // glass
              {
                sphere_material = std::make_shared<Dielectric>(1.5);
              }

              world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
          }
      }
  }

  auto material1 = std::make_shared<Dielectric>(1.5);
  world.Add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

  auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
  world.Add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

  auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
  world.Add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

  return world;
}

int main()
{
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 384;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  Camera camera(Point3(12, 2, 3), Point3::Zero, Vector3::Up, aspect_ratio, 20, 0.1);
  HittableList world = BuildWorld();

  std::cout << "P3" << std::endl;
  std::cout << image_width << ' ' << image_height << ' ' << std::endl;
  std::cout << "255" << std::endl;

  BRT::Progress progress(std::cerr, image_height - 1);

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
