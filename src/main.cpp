#include "brt.hpp"

using namespace BRT;

std::shared_ptr<Hittables::Hittable> BuildWorld()
{
  auto items = std::make_shared<Hittables::HittableList>();

  auto red = std::make_shared<Materials::Lambertian>(
    std::make_shared<Textures::SolidColor>(.65, .05, .05)
  );
  auto white = std::make_shared<Materials::Lambertian>(
    std::make_shared<Textures::SolidColor>(.73, .73, .73)
  );
  auto green = std::make_shared<Materials::Lambertian>(
    std::make_shared<Textures::SolidColor>(.12, .45, .15)
  );
  auto light = std::make_shared<Materials::DiffuseLight>(
    std::make_shared<Textures::SolidColor>(15, 15, 15)
  );

  // Walls, floor and ceiling
  items->Add(std::make_shared<Hittables::YZRectangle>(0, 555, 0, 555, 555, green));
  items->Add(std::make_shared<Hittables::YZRectangle>(0, 555, 0, 555, 0, red));
  items->Add(std::make_shared<Hittables::XZRectangle>(213, 343, 227, 332, 554, light));
  items->Add(std::make_shared<Hittables::XZRectangle>(0, 555, 0, 555, 0, white));
  items->Add(std::make_shared<Hittables::XZRectangle>(0, 555, 0, 555, 555, white));
  items->Add(std::make_shared<Hittables::XYRectangle>(0, 555, 0, 555, 555, white));

  // Boxes
  items->Add(std::make_shared<Hittables::Box>(Point3(130, 0, 65), Point3(295, 165, 230), white));
  items->Add(std::make_shared<Hittables::Box>(Point3(265, 0, 295), Point3(430, 330, 460), white));

  return items;
}

int main()
{
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 384;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);
  const auto fov = 40.0;
  const auto aperture = 0.0;
  const auto t0 = 0.0;
  const auto t1 = 1.0;

  const Color background(0, 0, 0);
  const Point3 look_from(278, 278, -800);
  const Point3 look_to(278, 278, 0);

  std::shared_ptr<Hittables::Hittable> world = BuildWorld();
  Render::Camera camera(look_from, look_to, Vector3::Up, aspect_ratio, fov, aperture, t0, t1);
  Render::Image image(image_width, image_height);
  Render::Renderer renderer(camera, world, background);

  renderer.Render(image);
  std::cout << image;

  return 0;
}
