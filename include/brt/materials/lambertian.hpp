#pragma once

#include "brt/color.hpp"
#include "brt/hit_info.hpp"
#include "brt/materials/material.hpp"
#include "brt/ray.hpp"

namespace BRT
{
  namespace Materials
  {
    class Lambertian : public Material
    {
      private:

        Color albedo;
      
      public:

        Lambertian(const Color&);

        virtual bool Scatter(const Ray&, const HitInfo&, Color&, Ray&) const;
    };
  }
}
