#pragma once

#include "brt/textures/texture.hpp"

namespace BRT
{
  namespace Textures
  {
    class SolidColor : public Texture
    {
      private:

        Color color;

      public:

        SolidColor();
        SolidColor(const Color& c);
        SolidColor(double r, double g, double b);

        virtual Color Value(double u, double v, const Point3& point) const;
    };
  }
}
