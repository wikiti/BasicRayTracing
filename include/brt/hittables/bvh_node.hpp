#pragma once

#include <memory>
#include <vector>

#include "brt/hittables/bounding_box.hpp"
#include "brt/hittables/hittable.hpp"
#include "brt/hittables/hittable_list.hpp"

namespace BRT
{
  namespace Hittables
  {
    class BVHNode: public Hittable
    {
      public:

        BVHNode();
        BVHNode(HittableList& list, double t0, double t1);
        BVHNode(std::vector<std::shared_ptr<Hittable>>& items, size_t start, size_t end,
          double t0, double t1);

        virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;

        virtual bool CalculateBoundingBox(double t0, double t1, BoundingBox& out) const;

      private:

        std::shared_ptr<Hittable> left;
        std::shared_ptr<Hittable> right;
        BoundingBox bounding_box;
    };
  }
}
