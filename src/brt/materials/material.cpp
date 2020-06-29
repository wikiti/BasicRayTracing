#include "brt/materials/material.hpp"

namespace BRT
{
  namespace Materials
  {
    Color Material::Emit(double u, double v, const Point3& p) const
    {
      return Color::Zero;
    }
  }
}
