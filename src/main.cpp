#include <iomanip>

#include "brt.hpp"

using namespace BRT;

inline double pdf(double x)
{
  return 3 * x * x / 8;
}

int main()
{
  int N = 1;
  auto sum = 0.0;
  for (int i = 0; i < N; i++)
  {
    auto x = std::pow(Utils::Random(0.0, 8.0), 1.0 / 3.0);
    sum += x * x / pdf(x);
  }
  std::cout << std::fixed << std::setprecision(12);
  std::cout << "I   = " << sum / N << '\n';
  std::cout << "8/3 = " << 8.0 / 3 << '\n';

  return 0;
}
