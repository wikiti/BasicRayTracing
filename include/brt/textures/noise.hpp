#pragma once

#include "brt/textures/texture.hpp"
#include "brt/misc/perlin.hpp"

namespace BRT
{
  namespace Textures
  {
    class Noise : public Texture
    {
      private:

        Misc::Perlin perlin;
        double scale;

      public:

        Noise();
        Noise(double scale);

        virtual Color Value(double u, double v, const Point3& point) const;
    };
  }
}
