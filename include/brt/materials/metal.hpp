#pragma once

#include "brt/materials/material.hpp"

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

        virtual bool Scatter(const Ray&, const Hittables::HitInfo&, Color&, Ray&, double&) const;
    };
  }
}
