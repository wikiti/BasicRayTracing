#pragma once

#include "rtiow/color.hpp"
#include "rtiow/hit_info.hpp"
#include "rtiow/ray.hpp"

namespace RTIOW
{
  namespace Materials
  {
    class Material
    {
      public:

        virtual bool Scatter(const Ray&, const HitInfo&, Color&, Ray&) const = 0;
    };
  }
}
