#pragma once

#include "brt/color.hpp"
#include "brt/hittables/hit_info.hpp"
#include "brt/materials/material.hpp"
#include "brt/ray.hpp"

namespace BRT
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

        virtual bool Scatter(const Ray&, const Hittables::HitInfo&, Color&, Ray&) const;
    };
  }
}