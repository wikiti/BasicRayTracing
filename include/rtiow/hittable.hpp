#pragma once

#include "rtiow/hit_info.hpp"
#include "rtiow/ray.hpp"

namespace RayTracingInOneWeekend
{
  class Hittable
  {
    public:

      virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const = 0;
  };
}
