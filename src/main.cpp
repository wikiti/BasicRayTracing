#include <iostream>

#include "color.hpp"
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
      RayTracingInOneWeekend::Color color = RayTracingInOneWeekend::Color(
        double(i) / (image_width - 1),
        double(j) / (image_height - 1),
        0.25
      );

      std::cout << color << std::endl;
    }
  }

  return 0;
}
