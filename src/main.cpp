#include <iostream>

#include "progress.hpp"

int main()
{
  // TODO: Image printer
  const int image_width = 256;
  const int image_height = 256;

  std::cout << "P3" << std::endl;
  std::cout << image_width << ' ' << image_height << ' ' << std::endl;
  std::cout << "255" << std::endl;

  RayTracingInOneWeekend::Progress progress(std::cerr, image_height - 1);

  for (int j = image_height - 1; j >= 0; --j)
  {
    progress.update(image_height - j - 1);

    for (int i = 0; i < image_width; ++i)
    {
      auto r = double(i) / (image_width - 1);
      auto g = double(j) / (image_height - 1);
      auto b = 0.25;

      int ir = static_cast<int>(255.999 * r);
      int ig = static_cast<int>(255.999 * g);
      int ib = static_cast<int>(255.999 * b);

      std::cout << ir << ' ' << ig << ' ' << ib << std::endl;
    }
  }

  return 0;
}
