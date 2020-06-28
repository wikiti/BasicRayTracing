#pragma once

#include "brt/point3.hpp"
#include "brt/vector3.hpp"

namespace BRT
{
  namespace Misc
  {
    class Perlin
    {
      public:

        Perlin();
        ~Perlin();

        double Noise(const Point3&) const;
      
      private:

        static int* GeneratePermutation();
        static void Permute(int* permutation, int n);
    
      private:

        static const int PointCount;

        Vector3* random_vectors;
        int* permutation_x;
        int* permutation_y;
        int* permutation_z;
    };
  }
}
