#include <iomanip>

#include "brt.hpp"

using namespace BRT;

int main()
{
  int inside_circle = 0;
  int inside_circle_stratified = 0;
  int sqrt_N = 10000;
  auto N = static_cast<double>(sqrt_N) * sqrt_N;

  for (int i = 0; i < sqrt_N; ++i)
  {
    for (int j = 0; j < sqrt_N; ++j)
    {
      // General
      auto x = Utils::Random(-1.0, 1.0);
      auto y = Utils::Random(-1.0, 1.0);
      if (x*x + y*y < 1)
      {
        ++inside_circle;
      }

      // Stratified
      x = Utils::Remap(((i + Utils::Random()) / sqrt_N), 0, 1, -1, 1);
      y = Utils::Remap(((j + Utils::Random()) / sqrt_N), 0, 1, -1, 1);
      if (x*x + y*y < 1)
      {
        ++inside_circle_stratified;
      }
    }
  }

  std::cout << std::fixed << std::setprecision(12);
  std::cout << "Regular    Estimate of Pi = " << 4 * double(inside_circle) / N << '\n';
  std::cout << "Stratified Estimate of Pi = " << 4 * double(inside_circle_stratified) / N << '\n';

  return 0;
}
