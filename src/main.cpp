#include <iomanip>

#include "brt.hpp"

using namespace BRT;

int main()
{
  int inside_circle = 0;
  int runs = 0;

  std::cout << std::fixed << std::setprecision(12);

  while (true)
  {
    ++runs;
    auto x = Utils::Random(-1.0, 1.0);
    auto y = Utils::Random(-1.0, 1.0);

    if (x*x + y*y < 1)
    {
      ++inside_circle;
    }

    if (runs % 100000 == 0)
    {
      std::cout << "Estimate of Pi = " << 4 * double(inside_circle) / runs << '\n';
    }
  }

  return 0;
}
