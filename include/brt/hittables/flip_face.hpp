#pragma once

#include <memory>

#include "brt/hittables/hittable.hpp"

namespace BRT
{
  namespace Hittables
  {
    class FlipFace : public Hittable
    {
      private:

        std::shared_ptr<Hittable> hittable;

      public:

        FlipFace(std::shared_ptr<Hittable> hittable);

        virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;

        virtual bool CalculateBoundingBox(double t0, double t1, BoundingBox& out) const;
    };
  }
}
