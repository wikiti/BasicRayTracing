#pragma once

#include "rtiow/hit_info.hpp"
#include "rtiow/ray.hpp"

namespace RTIOW
{
  class Hittable
  {
    public:

      virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const = 0;
      virtual bool Hit(const Ray&, HitInfo&) const;
  };
}
