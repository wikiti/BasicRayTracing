#pragma once

#include "brt/materials/material.hpp"

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

        virtual bool Scatter(const Ray&, const Hittables::HitInfo&, Color&, Ray&, double&) const;

      private:

        bool ShouldReflect(const Vector3&, const Hittables::HitInfo&, double) const;
        double Schlick(double, double) const;
    };
  }
}
