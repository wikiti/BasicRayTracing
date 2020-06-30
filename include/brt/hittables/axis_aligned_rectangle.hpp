#pragma once

#include <memory>

#include "brt/hittables/hittable.hpp"
#include "brt/materials/material.hpp"
#include "brt/misc/plane.hpp"
#include "brt/point3.hpp"

namespace BRT
{
  namespace Hittables
  {
    template <Misc::Plane>
    class AxisAlignedRectangle: public Hittable
    {
      private:

        double a0, a1;
        double b0, b1;
        double k;

        std::shared_ptr<Materials::Material> material;

      public:

        AxisAlignedRectangle();
        AxisAlignedRectangle(double x0, double x1, double y0, double y1, double z,
          std::shared_ptr<Materials::Material> material);

        virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;
        virtual bool CalculateBoundingBox(double t0, double t1, BoundingBox& out) const;

      private:

        int AIndex() const;
        int BIndex() const;
        int KIndex() const;
    };

    using XYRectangle = AxisAlignedRectangle<Misc::Plane::XY>;
    using XZRectangle = AxisAlignedRectangle<Misc::Plane::XZ>;
    using YZRectangle = AxisAlignedRectangle<Misc::Plane::YZ>;
  }
}
