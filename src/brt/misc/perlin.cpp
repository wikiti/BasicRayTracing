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

      int i = std::floor(point.X());
      int j = std::floor(point.Y());
      int k = std::floor(point.Z());

      double c[2][2][2];

      for (int di = 0; di < 2; ++di)
      {
        for (int dj = 0; dj < 2; ++dj)
        {
          for (int dk = 0; dk < 2; ++dk)
          {
            c[di][dj][dk] = random_float[
              permutation_x[(i+di) & 255] ^
              permutation_y[(j+dj) & 255] ^
              permutation_z[(k+dk) & 255]
            ];
          }
        }
      }

      return Utils::TrilinearInterpolation(c, u, v, w);
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
