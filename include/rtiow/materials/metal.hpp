#pragma once

#include "rtiow/color.hpp"
#include "rtiow/hit_info.hpp"
#include "rtiow/materials/material.hpp"
#include "rtiow/ray.hpp"

namespace RTIOW
{
  namespace Materials
  {
    class Metal : public Material
    {
      private:

        Color albedo;
        double fuzz;
      
      public:

        Metal(const Color&, double);

        virtual bool Scatter(const Ray&, const HitInfo&, Color&, Ray&) const;
    };
  }
}
