#pragma once

#include "hit_info.hpp"
#include "ray.hpp"

namespace RayTracingInOneWeekend
{
  class Hittable
  {
    public:

      virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const = 0;
  };
}
