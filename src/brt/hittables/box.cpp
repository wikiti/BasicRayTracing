#include "brt/hittables/box.hpp"
#include "brt/hittables/axis_aligned_rectangle.hpp"

namespace BRT
{
  namespace Hittables
  {
    Box::Box()
    {}

    Box::Box(const Point3& from, const Point3& to, std::shared_ptr<Materials::Material> mat) :
      from(from), to(to)
    {
      // Front and back
      sides.Add(std::make_shared<XYRectangle>(from.X(), to.X(), from.Y(), to.Y(), to.Z(), mat));
      sides.Add(std::make_shared<XYRectangle>(from.X(), to.X(), from.Y(), to.Y(), from.Z(), mat));

      // Up and down
      sides.Add(std::make_shared<XZRectangle>(from.X(), to.X(), from.Z(), to.Z(), to.Y(), mat));
      sides.Add(std::make_shared<XZRectangle>(from.X(), to.X(), from.Z(), to.Z(), from.Y(), mat));

      // Left and right
      sides.Add(std::make_shared<YZRectangle>(from.Y(), to.Y(), from.Z(), to.Z(), to.X(), mat));
      sides.Add(std::make_shared<YZRectangle>(from.Y(), to.Y(), from.Z(), to.Z(), from.X(), mat));
    }

    bool Box::Hit(const Ray& ray, double t_min, double t_max, HitInfo& hit_info) const
    {
      return sides.Hit(ray, t_min, t_max, hit_info);
    }

    bool Box::CalculateBoundingBox(double t0, double t1, BoundingBox& out) const
    {
      out = BoundingBox(from, to);
      return true;
    }
  }
}
