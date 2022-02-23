#pragma once

#include "brt/color.hpp"
#include "brt/hittables/hit_info.hpp"
#include "brt/ray.hpp"

namespace BRT
{
  namespace Materials
  {
    class Material
    {
      public:

        virtual bool Scatter(const Ray&, const Hittables::HitInfo&, Color&, Ray&, double& pdf) const = 0;
        virtual double ScatteringPdf(const Ray&, const Hittables::HitInfo&, const Ray&) const; // TODO: Apply "= 0"
        virtual Color Emit(double u, double v, const Point3& p) const;
    };
  }
}
