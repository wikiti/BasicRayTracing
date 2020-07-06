#include <iomanip>

#include "brt.hpp"

using namespace BRT;

int main()
{
  int N = 100000;
  int inside_circle = 0;

  for (int i = 0; i < N; ++i)
  {
    auto x = Utils::Random(-1.0, 1.0);
    auto y = Utils::Random(-1.0, 1.0);

    if (x*x + y*y < 1)
    {
      ++inside_circle;
    }
  }

  std::cout << std::fixed << std::setprecision(12);
  std::cout << "Estimate of Pi = " << 4 * double(inside_circle) / N << '\n';

  return 0;
}
