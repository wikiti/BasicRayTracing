#include <cmath>

#include "brt/misc/perlin.hpp"
#include "brt/utils.hpp"

namespace BRT
{
  namespace Misc
  {
    const int Perlin::PointCount = 256;

    Perlin::Perlin()
    {
      random_float = new double[PointCount];
      for (int i = 0; i < PointCount; ++i)
      {
        random_float[i] = Utils::Random();
      }

      permutation_x = GeneratePermutation();
      permutation_y = GeneratePermutation();
      permutation_z = GeneratePermutation();
    }

    Perlin::~Perlin()
    {
      delete[] random_float;
      delete[] permutation_x;
      delete[] permutation_y;
      delete[] permutation_z;
    }

    double Perlin::Noise(const Point3& point) const
    {
      auto u = point.X() - std::floor(point.X());
      auto v = point.Y() - std::floor(point.Y());
      auto w = point.Z() - std::floor(point.Z());

      auto i = static_cast<int>(4 * point.X()) & 255;
      auto j = static_cast<int>(4 * point.Y()) & 255;
      auto k = static_cast<int>(4 * point.Z()) & 255;

      return random_float[permutation_x[i] ^ permutation_y[j] ^ permutation_z[k]];
    }

    int* Perlin::GeneratePermutation()
    {
      auto permutation = new int[PointCount];

      for (int i = 0; i < PointCount; ++i)
      {
        permutation[i] = i;
      }

      Permute(permutation, PointCount);
      return permutation;
    }

    void Perlin::Permute(int* permutation, int n)
    {
      for (int i = n - 1; i > 0; --i)
      {
        std::swap(permutation[i], permutation[Utils::Random(0, i + 1)]);
      }
    }
  }
}
