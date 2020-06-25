#include "brt.hpp"

using BRT::Camera;
using BRT::Color;
using BRT::Hittables::BVHNode;
using BRT::Hittables::HitInfo;
using BRT::Hittables::Hittable;
using BRT::Hittables::HittableList;
using BRT::Hittables::MovingSphere;
using BRT::Hittables::Sphere;
using BRT::Materials::Dielectric;
using BRT::Materials::Lambertian;
using BRT::Materials::Material;
using BRT::Materials::Metal;
using BRT::Textures::SolidColor;
using BRT::MovingPoint3;
using BRT::Point3;
using BRT::Render::Image;
using BRT::Render::Renderer;
using BRT::Utils;
using BRT::Vector3;

std::shared_ptr<Hittable> BuildWorld(double t0, double t1)
{
  HittableList world;

  auto ground_material = std::make_shared<Lambertian>(std::make_shared<SolidColor>(0.5, 0.5, 0.5));
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
                auto albedo = std::make_shared<SolidColor>(Color::Random() * Color::Random());
                sphere_material = std::make_shared<Lambertian>(albedo);
                MovingPoint3 moving_center(
                  center, center + Vector3(0, Utils::Random(0.0, 0.5), 0),
                  t0, t1
                );
                world.Add(std::make_shared<MovingSphere>(moving_center, 0.2, sphere_material));
              }
              else if (choose_mat < 0.95) // metal
              {
                auto albedo = Color::Random(0.5, 1);
                auto fuzz = Utils::Random(0.0, 0.5);
                sphere_material = std::make_shared<Metal>(albedo, fuzz);
                world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
              }
              else // glass
              {
                sphere_material = std::make_shared<Dielectric>(1.5);
                world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
              }
          }
      }
  }

  auto material1 = std::make_shared<Dielectric>(1.5);
  world.Add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

  auto material2 = std::make_shared<Lambertian>(std::make_shared<SolidColor>(0.4, 0.2, 0.1));
  world.Add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

  auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
  world.Add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

  return std::make_shared<BVHNode>(world, t0, t1);
}

int main()
{
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 384;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);
  const auto t0 = 0;
  const auto t1 = 1;

  std::shared_ptr<Hittable> world = BuildWorld(t0, t1);
  Camera camera(Point3(13, 2, 3), Point3::Zero, Vector3::Up, aspect_ratio, 20, 0.0, t0, t1);
  Image image(image_width, image_height);
  Renderer renderer(camera, world);

  renderer.Render(image);
  std::cout << image;

  return 0;
}
