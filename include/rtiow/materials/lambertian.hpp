#pragma once

#include "rtiow/color.hpp"
#include "rtiow/hit_info.hpp"
#include "rtiow/materials/material.hpp"
#include "rtiow/ray.hpp"

namespace RTIOW
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
