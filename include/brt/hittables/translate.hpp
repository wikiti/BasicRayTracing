#pragma once

#include <memory>

#include "brt/hittables/hittable.hpp"

namespace BRT
{
  namespace Hittables
  {
    class Translate: public Hittable
    {
      public:

        Translate(std::shared_ptr<Hittable>, const Vector3& offset);

        virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;

        virtual bool CalculateBoundingBox(double t0, double t1, BoundingBox& out) const;

      private:

        std::shared_ptr<Hittable> hittable;
        Vector3 offset;
    };
  }
}
