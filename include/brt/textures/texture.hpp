#pragma once

#include "brt/color.hpp"
#include "brt/point3.hpp"

namespace BRT
{
  namespace Textures
  {
    class Texture
    {
      public:

        virtual Color Value(double u, double v, const Point3&) const = 0;
    };
  }
}
