#pragma once

#include <memory>
#include <vector>

#include "rtiow/hittable.hpp"

namespace RayTracingInOneWeekend
{
  class HittableList : public Hittable
  {
    public:
      
      HittableList();
      HittableList(std::shared_ptr<Hittable>);

      void Clear();
      void Add(std::shared_ptr<Hittable>);

      virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;

    private:

      std::vector<std::shared_ptr<Hittable>> items;
  };
}
