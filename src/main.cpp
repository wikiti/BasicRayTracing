#include <iomanip>

#include "brt.hpp"

using namespace BRT;

inline double pdf(const Vector3 &p)
{
  return 1.0 / (4 * Utils::Pi);
}

int main()
{
  int N = 1000000;
  auto sum = 0.0;

  for (int i = 0; i < N; i++)
  {
    Vector3 d = Utils::RandomUnitVector();
    auto cosine_squared = d.Z() * d.Z();
    sum += cosine_squared / pdf(d);
  }

  std::cout << std::fixed << std::setprecision(12);
  std::cout << "I          = " << sum / N << '\n';
  std::cout << "(4/3) * pi = " << (4.0 / 3) * Utils::Pi << '\n';

  return 0;
}
