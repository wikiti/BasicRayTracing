#include "brt.hpp"

using namespace BRT;

std::shared_ptr<Hittables::Hittable> BuildWorld()
{
  auto items = std::make_shared<Hittables::HittableList>();

  auto ground_tiles = std::make_shared<Hittables::HittableList>();
  auto ground_material = std::make_shared<Materials::Lambertian>(
    std::make_shared<Textures::SolidColor>(0.48, 0.83, 0.53)
  );

  const int boxes_per_side = 20;

  for (int i = 0; i < boxes_per_side; ++i) {
    for (int j = 0; j < boxes_per_side; ++j) {
      auto w = 100.0;
      auto x0 = -1000.0 + i * w;
      auto z0 = -1000.0 + j * w;
      auto y0 = 0.0;
      auto x1 = x0 + w;
      auto y1 = Utils::Random(1.0, 101.0);
      auto z1 = z0 + w;

      auto tile = std::make_shared<Hittables::Box>(
        Point3(x0, y0, z0), 
        Point3(x1, y1, z1),
        ground_material
      );

      ground_tiles->Add(tile);
    }
  }

  items->Add(std::make_shared<Hittables::BVHNode>(*ground_tiles, 0, 1));

  auto light = std::make_shared<Hittables::XZRectangle>(
    123, 423,
    147, 412,
    554,
    std::make_shared<Materials::DiffuseLight>(std::make_shared<Textures::SolidColor>(7, 7, 7))
  );
  items->Add(light);

  auto moving_sphere = std::make_shared<Hittables::MovingSphere>(
    MovingPoint3(Point3(400, 400, 200), Point3(430, 400, 200), 0, 1),
    50,
    std::make_shared<Materials::Lambertian>(std::make_shared<Textures::SolidColor>(0.7, 0.3, 0.1))
  );
  items->Add(moving_sphere);

  auto glass_sphere = std::make_shared<Hittables::Sphere>(
    Point3(260, 150, 45),
    50,
    std::make_shared<Materials::Dielectric>(1.5)
  );
  items->Add(glass_sphere);

  auto metalic_sphere = std::make_shared<Hittables::Sphere>(
    Point3(0, 150, 145),
    50,
    std::make_shared<Materials::Metal>(Color(0.8, 0.8, 0.9), 10.0)
  );
  items->Add(metalic_sphere);

  auto fog_boundary = std::make_shared<Hittables::Sphere>(
    Point3(360, 150, 145),
    70,
    std::make_shared<Materials::Dielectric>(1.5)
  );
  auto fog = std::make_shared<Hittables::ConstantDensityMedium>(
    fog_boundary,
    0.2,
    std::make_shared<Materials::Isotropic>(std::make_shared<Textures::SolidColor>(0.2, 0.4, 0.9))
  );
  items->Add(fog_boundary);
  items->Add(fog);

  fog_boundary = std::make_shared<Hittables::Sphere>(
    Point3(0, 0, 0),
    5000,
    std::make_shared<Materials::Dielectric>(1.5)
  );
  fog = std::make_shared<Hittables::ConstantDensityMedium>(
    fog_boundary,
    .0001,
    std::make_shared<Materials::Isotropic>(std::make_shared<Textures::SolidColor>(1, 1, 1))
  );
  items->Add(fog);

  auto earth_material = std::make_shared<Materials::Lambertian>(
    std::make_shared<Textures::Image>("assets/earthmap.jpg")
  );
  auto earth = std::make_shared<Hittables::Sphere>(
    Point3(400, 200, 400),
    100,
    earth_material
  );
  items->Add(earth);

  auto perlin_material = std::make_shared<Materials::Lambertian>(
    std::make_shared<Textures::Noise>(0.1)
  );
  auto perlin_sphere = std::make_shared<Hittables::Sphere>(
    Point3(220, 280, 300),
    80,
    perlin_material
  );
  items->Add(perlin_sphere);

  auto box_of_spheres = std::make_shared<Hittables::HittableList>();
  auto white_material = std::make_shared<Materials::Lambertian>(
    std::make_shared<Textures::SolidColor>(.73, .73, .73)
  );
  for (int j = 0; j < 1000; j++) {
    auto sphere = std::make_shared<Hittables::Sphere>(
      Point3::Random(0, 165),
      10,
      white_material
    );
    box_of_spheres->Add(sphere);
  }

  items->Add(std::make_shared<Hittables::Translate>(
    std::make_shared<Hittables::RotateY>(
      std::make_shared<Hittables::BVHNode>(*box_of_spheres, 0.0, 1.0), 15),
      Vector3(-100, 270, 395)
    )
  );

  return items;
}

int main()
{
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 600;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);
  const auto fov = 40.0;
  const auto aperture = 0.0;
  const auto t0 = 0.0;
  const auto t1 = 1.0;

  const Color background(0, 0, 0);
  const Point3 look_from(478, 278, -600);
  const Point3 look_to(278, 278, 0);

  std::shared_ptr<Hittables::Hittable> world = BuildWorld();
  Render::Camera camera(look_from, look_to, Vector3::Up, aspect_ratio, fov, aperture, t0, t1);
  Render::Image image(image_width, image_height);
  Render::Renderer renderer(camera, world, background);

  renderer.Render(image, 10000);
  std::cout << image;

  return 0;
}
