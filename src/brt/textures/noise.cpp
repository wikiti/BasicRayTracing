#include "brt/textures/noise.hpp"

namespace BRT
{
  namespace Textures
  {
    Noise::Noise() : scale(1.0)
    {}

    Noise::Noise(double scale) : scale(scale)
    {}

    Color Noise::Value(double u, double v, const Point3& point) const
    {
      return Color(1, 1, 1) * perlin.Noise(scale * point);
    }
  }
}
