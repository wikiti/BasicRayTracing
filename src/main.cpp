#include <iomanip>

#include "brt.hpp"

using namespace BRT;

int main()
{
  int N = 1000000;
  auto sum = 0.0;
  for (int i = 0; i < N; i++)
  {
    auto x = Utils::Random(0.0, 2.0);
    sum += x * x;
  }
  std::cout << std::fixed << std::setprecision(12);
  std::cout << "I   = " << 2 * sum / N << '\n';
  std::cout << "8/3 = " << 8.0 / 3 << '\n';

  return 0;
}
