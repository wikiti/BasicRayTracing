#include "brt.hpp"

using namespace BRT;

std::shared_ptr<Hittables::Hittable> BuildWorld()
{
  auto texture = std::make_shared<Textures::Image>("assets/earthmap.jpg");
  auto items = std::make_shared<Hittables::HittableList>();

  items->Add(
    std::make_shared<Hittables::Sphere>(
      Point3(0, 0, 0),
      2,
      std::make_shared<Materials::Lambertian>(texture)
    )
  );

  return items;
}

int main()
{
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 384;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);
  const auto t0 = 0.0;
  const auto t1 = 1.0;

  std::shared_ptr<Hittables::Hittable> world = BuildWorld();
  Render::Camera camera(Point3(13, 2, 3), Point3::Zero, Vector3::Up, aspect_ratio, 20, 0.0, t0, t1);
  Render::Image image(image_width, image_height);
  Render::Renderer renderer(camera, world);

  renderer.Render(image);
  std::cout << image;

  return 0;
}
