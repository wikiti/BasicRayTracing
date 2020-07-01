#pragma once

#include <memory>

#include "brt/hittables/hittable.hpp"

namespace BRT
{
  namespace Hittables
  {
    class ConstantDensityMedium : public Hittable
    {
      private:

        std::shared_ptr<Hittable> boundary;
        std::shared_ptr<Materials::Material> phase_function;
        double density;

      public:

        ConstantDensityMedium(std::shared_ptr<Hittable> boundary, double density,
          std::shared_ptr<Materials::Material> phase_function);
      
        virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;

        virtual bool CalculateBoundingBox(double t0, double t1, BoundingBox& out) const;
    };
  }
}
