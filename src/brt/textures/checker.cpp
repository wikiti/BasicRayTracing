#include <cmath>

#include "brt/textures/checker.hpp"

namespace BRT
{
  namespace Textures
  {
    Checker::Checker()
    {}

    Checker::Checker(std::shared_ptr<Texture> odd, std::shared_ptr<Texture> even, double scale) :
       odd(odd), even(even), scale(scale)
    {}

    Color Checker::Value(double u, double v, const Point3& point) const
    {
      auto sines = std::sin(scale * point.X()) * std::sin(scale * point.Y()) *
        std::sin(scale * point.Z());
      auto texture = (sines < 0) ? odd : even;
      return texture->Value(u, v, point);
    }
  }
}
