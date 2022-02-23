#include <iomanip>

#include "brt.hpp"

using namespace BRT;

inline double pdf(double x)
{
  return 0.5 * x;
}

int main()
{
  int N = 1000000;
  auto sum = 0.0;
  for (int i = 0; i < N; i++)
  {
    auto x = std::sqrt(Utils::Random(0.0, 4.0));
    sum += x * x / pdf(x);
  }
  std::cout << std::fixed << std::setprecision(12);
  std::cout << "I   = " << sum / N << '\n';
  std::cout << "8/3 = " << 8.0 / 3 << '\n';

  return 0;
}
