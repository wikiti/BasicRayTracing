#pragma once

#include "rtiow/color.hpp"
#include "rtiow/hit_info.hpp"
#include "rtiow/materials/material.hpp"
#include "rtiow/ray.hpp"

namespace RTIOW
{
  namespace Materials
  {
    class Dielectric : public Material
    {
      private:

        double refraction_index;
      
      public:

        Dielectric(double);

        virtual bool Scatter(const Ray&, const HitInfo&, Color&, Ray&) const;
    };
  }
}
