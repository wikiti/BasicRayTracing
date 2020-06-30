#include "brt/hittables/axis_aligned_rectangle.hpp"
#include "brt/utils.hpp"

namespace BRT
{
  namespace Hittables
  {
    template <Misc::Plane P> 
    AxisAlignedRectangle<P>::AxisAlignedRectangle()
    {}

    template <Misc::Plane P>
    AxisAlignedRectangle<P>::AxisAlignedRectangle(double a0, double a1, double b0, double b1, double k,
      std::shared_ptr<Materials::Material> material) :
      a0(a0), a1(a1), b0(b0), b1(b1), k(k), material(material)
    {}

    template <Misc::Plane P>
    bool AxisAlignedRectangle<P>::Hit(const Ray& r, double t_min, double t_max, HitInfo& hit_info) const
    {
      auto t = (k - r.Origin()[KIndex()]) / r.Direction()[KIndex()];
      if (t < t_min || t > t_max)
      {
        return false;
      }

      const auto a = r.Origin()[AIndex()] + t * r.Direction()[AIndex()];
      const auto b = r.Origin()[BIndex()] + t * r.Direction()[BIndex()];
      
      if (a < a0 || a > a1 || b < b0 || b > b1)
      {
        return false;
      }

      hit_info.u = (a - a0) / (a1 - a0);
      hit_info.v = (b - b0) / (b1 - b0);
      hit_info.distance = t;

      Vector3 outward_normal;
      outward_normal[KIndex()] = 1.0;

      hit_info.SetFaceNormal(r, outward_normal);
      hit_info.material = material;
      hit_info.point = r.At(t);

      return true;
    }

    template <Misc::Plane P>
    bool AxisAlignedRectangle<P>::CalculateBoundingBox(double t0, double t1, BoundingBox& out) const
    {
      switch (P)
      {
        case Misc::Plane::XY:
          out = BoundingBox(Point3(a0, b0, k - Utils::Epsilon), Point3(a1, b1, k + Utils::Epsilon));
          break;
        case Misc::Plane::XZ:
          out = BoundingBox(Point3(a0, k - Utils::Epsilon, b0), Point3(a1, k + Utils::Epsilon, b1));
          break;
        default:
          out = BoundingBox(Point3(k - Utils::Epsilon, a0, b0), Point3(k + Utils::Epsilon, a1, b1));
          break;
      }

      return true;
    }

    template <Misc::Plane P>
    int AxisAlignedRectangle<P>::AIndex() const
    {
      switch (P)
      {
        case Misc::Plane::YZ:
          return 1;
        default:
          return 0;
      }
    }

    template <Misc::Plane P>
    int AxisAlignedRectangle<P>::BIndex() const
    {
      switch (P)
      {
        case Misc::Plane::XY:
          return 1;
        default:
          return 2;
      }
    }

    template <Misc::Plane P>
    int AxisAlignedRectangle<P>::KIndex() const
    {
      switch (P)
      {
        case Misc::Plane::XY:
          return 2;
        case Misc::Plane::XZ:
          return 1;
        default:
          return 0;
      }
    }

    // NOTE: Force template specialization implementation to avoid undefined errors
    template class AxisAlignedRectangle<Misc::Plane::XY>;
    template class AxisAlignedRectangle<Misc::Plane::XZ>;
    template class AxisAlignedRectangle<Misc::Plane::YZ>;
  }
}
