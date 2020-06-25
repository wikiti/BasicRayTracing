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
using BRT::Textures::Noise;
using BRT::Textures::SolidColor;
using BRT::MovingPoint3;
using BRT::Point3;
using BRT::Render::Image;
using BRT::Render::Renderer;
using BRT::Utils;
using BRT::Vector3;

std::shared_ptr<Hittable> BuildWorld()
{
  auto tex = std::make_shared<Noise>();
  auto items = std::make_shared<HittableList>();
  items->Add(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, std::make_shared<Lambertian>(tex)));
  items->Add(std::make_shared<Sphere>(Point3(0, 2, 0), 2, std::make_shared<Lambertian>(tex)));
  return items;
}

int main()
{
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 384;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);
  const auto t0 = 0.0;
  const auto t1 = 1.0;

  std::shared_ptr<Hittable> world = BuildWorld();
  Camera camera(Point3(13, 2, 3), Point3::Zero, Vector3::Up, aspect_ratio, 20, 0.0, t0, t1);
  Image image(image_width, image_height);
  Renderer renderer(camera, world);

  renderer.Render(image);
  std::cout << image;

  return 0;
}
