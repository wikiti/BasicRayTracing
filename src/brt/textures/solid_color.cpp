#include "brt/textures/solid_color.hpp"

namespace BRT
{
  namespace Textures
  {
    SolidColor::SolidColor()
    {}

    SolidColor::SolidColor(const Color& c) : color(c)
    {}

    SolidColor::SolidColor(double r, double g, double b) : color(Color(r, g, b))
    {}

    Color SolidColor::Value(double u, double v, const Point3& point) const
    {
      return color;
    }
  }
}
