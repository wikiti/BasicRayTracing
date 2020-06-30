#pragma once

#include <memory>

#include "brt/hittables/hittable.hpp"
#include "brt/materials/material.hpp"
#include "brt/misc/axis.hpp"

namespace BRT
{
  namespace Hittables
  {
    template <Misc::Axis>
    class Rotate: public Hittable
    {
      private:

        std::shared_ptr<Hittable> hittable;
        double sin_theta, cos_theta;

        double has_box;
        BoundingBox bounding_box;

      public:

        Rotate();
        Rotate(std::shared_ptr<Hittable> hittable, double angle);

        virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;
        virtual bool CalculateBoundingBox(double t0, double t1, BoundingBox& out) const;
      
      private:

        void PrecalculateBoundingBox();

        Vector3 NewPosition(double x, double y, double z, bool invert = false) const;
        Vector3 NewPosition(const Vector3& v, bool invert = false) const;
    };

    using RotateX = Rotate<Misc::Axis::X>;
    using RotateY = Rotate<Misc::Axis::Y>;
    using RotateZ = Rotate<Misc::Axis::Z>;
  }
}
