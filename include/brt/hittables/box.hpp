#pragma once

#include <memory>

#include "brt/hittables/hittable.hpp"
#include "brt/hittables/hittable_list.hpp"
#include "brt/materials/material.hpp"
#include "brt/point3.hpp"

namespace BRT
{
  namespace Hittables
  {
    class Box : public Hittable
    {
      private:

        Point3 from;
        Point3 to;

        HittableList sides;

      public:

        Box();
        Box(const Point3& from, const Point3& to, std::shared_ptr<Materials::Material> material);

        virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;

        virtual bool CalculateBoundingBox(double t0, double t1, BoundingBox& out) const;
    };
  }
}
