#include "brt/textures/noise.hpp"
#include "brt/utils.hpp"

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
      return Color(1, 1, 1) * Utils::Remap(perlin.Noise(scale * point), -1, 1, 0, 1);
    }
  }
}
