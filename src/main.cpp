#include <iomanip>

#include "brt.hpp"

using namespace BRT;

std::shared_ptr<Hittables::HittableList> CornellBox()
{
  auto objects = std::make_shared<Hittables::HittableList>();

  auto red = std::make_shared<Materials::Lambertian>(Color(.65, .05, .05));
  auto white = std::make_shared<Materials::Lambertian>(Color(.73, .73, .73));
  auto green = std::make_shared<Materials::Lambertian>(Color(.12, .45, .15));
  auto light = std::make_shared<Materials::DiffuseLight>(Color(15, 15, 15));

  objects->Add(std::make_shared<Hittables::YZRectangle>(0, 555, 0, 555, 555, green));
  objects->Add(std::make_shared<Hittables::YZRectangle>(0, 555, 0, 555, 0, red));
  objects->Add(std::make_shared<Hittables::XZRectangle>(213, 343, 227, 332, 554, light));
  objects->Add(std::make_shared<Hittables::XZRectangle>(0, 555, 0, 555, 555, white));
  objects->Add(std::make_shared<Hittables::XZRectangle>(0, 555, 0, 555, 0, white));
  objects->Add(std::make_shared<Hittables::XYRectangle>(0, 555, 0, 555, 555, white));

  std::shared_ptr<Hittables::Hittable> box1 =
      std::make_shared<Hittables::Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
  box1 = std::make_shared<Hittables::RotateY>(box1, 15);
  box1 = std::make_shared<Hittables::Translate>(box1, Vector3(265, 0, 295));
  objects->Add(box1);

  std::shared_ptr<Hittables::Hittable> box2 =
      std::make_shared<Hittables::Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
  box2 = std::make_shared<Hittables::RotateY>(box2, -18);
  box2 = std::make_shared<Hittables::Translate>(box2, Vector3(130, 0, 65));
  objects->Add(box2);

  return objects;
}

int main()
{
  const auto aspect_ratio = 1.0 / 1.0;
  const auto image_width = 600;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);

  const auto fov = 40.0;
  const auto aperture = 0.0;

  const Color background(0, 0, 0);
  const Point3 look_from(278, 278, -800);
  const Point3 look_at(278, 278, 0);

  std::shared_ptr<Hittables::Hittable> world = CornellBox();

  Render::Camera camera(look_from, look_at, Vector3::Up, aspect_ratio, fov, aperture);
  Render::Image image(image_width, image_height);
  Render::Renderer renderer(camera, world, background);

  renderer.Render(image, 100, 50);
  std::cout << image;

  return 0;
}
