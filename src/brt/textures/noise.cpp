#include <cmath>

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
      return Color::White *
        Utils::Remap(std::sin(scale * point.Z() + 10 * perlin.Turbulence(scale * point)),
                     -1.0, 1.0,
                     0.0, 1.0);
    }
  }
}
