#pragma once

#include "brt/hittables/hit_info.hpp"
#include "brt/ray.hpp"

namespace BRT
{
  namespace Hittables
  {
    class Hittable
    {
      public:

        virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const = 0;
        virtual bool Hit(const Ray&, HitInfo&) const;
    };
  }
}
