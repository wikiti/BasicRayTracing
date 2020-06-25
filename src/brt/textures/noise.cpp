#include "brt/textures/noise.hpp"

namespace BRT
{
  namespace Textures
  {
    Noise::Noise()
    {}

    Color Noise::Value(double u, double v, const Point3& point) const
    {
      return Color(1, 1, 1) * perlin.Noise(point);
    }
  }
}
