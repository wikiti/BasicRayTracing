#pragma once

#include "brt/color.hpp"
#include "brt/hittables/hit_info.hpp"
#include "brt/materials/material.hpp"
#include "brt/ray.hpp"

namespace BRT
{
  namespace Materials
  {
    class Dielectric : public Material
    {
      private:

        double refraction_index;
      
      public:

        Dielectric(double);

        virtual bool Scatter(const Ray&, const Hittables::HitInfo&, Color&, Ray&) const;

      private:

        bool ShouldReflect(const Vector3&, const Hittables::HitInfo&, double) const;
        double Schlick(double, double) const;
    };
  }
}
