#include "brt/materials/material.hpp"

namespace BRT
{
  namespace Materials
  {
    double Material::ScatteringPdf(const Ray&, const Hittables::HitInfo&, const Ray&) const
    {
      return 0;
    }

    Color Material::Emit(const Ray& ray, const Hittables::HitInfo& hit_info, double u, double v, const Point3& p) const
    {
      return Color::Zero;
    }
  }
}
