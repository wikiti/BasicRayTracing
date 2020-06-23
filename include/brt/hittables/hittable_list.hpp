#pragma once

#include <memory>
#include <vector>

#include "brt/hittables/hittable.hpp"

namespace BRT
{
  namespace Hittables
  {
    class HittableList : public Hittable
    {
      public:

        HittableList();
        HittableList(std::shared_ptr<Hittable>);
        HittableList(const HittableList&);

        std::vector<std::shared_ptr<Hittable>>& Items();
        unsigned int Size();

        void Clear();
        void Add(std::shared_ptr<Hittable>);

        virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;

        virtual bool CalculateBoundingBox(double t0, double t1, BoundingBox& out) const;

      private:

        std::vector<std::shared_ptr<Hittable>> items;
    };
  }
}
