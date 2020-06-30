#include "brt.hpp"

using namespace BRT;

std::shared_ptr<Hittables::Hittable> BuildWorld()
{
  auto items = std::make_shared<Hittables::HittableList>();

  auto perlin_texture = std::make_shared<Textures::Noise>(4);
  auto perlin_material = std::make_shared<Materials::Lambertian>(perlin_texture);

  items->Add(std::make_shared<Hittables::Sphere>(Point3(0, -1000, 0), 1000, perlin_material));
  items->Add(std::make_shared<Hittables::Sphere>(Point3(0, 2, 0), 2, perlin_material));

  auto light_texture = std::make_shared<Textures::SolidColor>(4, 4, 4);
  auto light_material = std::make_shared<Materials::DiffuseLight>(light_texture);

  auto light_texture_pink = std::make_shared<Textures::SolidColor>(1, 0.2, 0.2);
  auto light_material_pink = std::make_shared<Materials::DiffuseLight>(light_texture_pink);

  items->Add(std::make_shared<Hittables::Sphere>(Point3(0, 7, 0), 2, light_material));
  items->Add(std::make_shared<Hittables::XYRectangle>(3, 5, 1, 3, -2, light_material_pink));

  return items;
}

int main()
{
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 384;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);
  const auto fov = 20.0;
  const auto aperture = 0.0;
  const auto t0 = 0.0;
  const auto t1 = 1.0;

  const Color background(0, 0, 0);
  const Point3 look_from(25, 2, 4);
  const Point3 look_to(0, 2, 0);

  std::shared_ptr<Hittables::Hittable> world = BuildWorld();
  Render::Camera camera(look_from, look_to, Vector3::Up, aspect_ratio, fov, aperture, t0, t1);
  Render::Image image(image_width, image_height);
  Render::Renderer renderer(camera, world, background);

  renderer.Render(image);
  std::cout << image;

  return 0;
}
