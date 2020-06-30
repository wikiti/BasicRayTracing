#include "brt/hittables/translate.hpp"

namespace BRT
{
  namespace Hittables
  {
    Translate::Translate(std::shared_ptr<Hittable> hittable, const Vector3& offset) :
      hittable(hittable), offset(offset)
    {}

    bool Translate::Hit(const Ray& ray, double t_min, double t_max, HitInfo& hit_info) const
    {
      Ray moved_ray(ray.Origin() - offset, ray.Direction(), ray.Time());
      if (!hittable->Hit(moved_ray, t_min, t_max, hit_info))
      {
        return false;
      }

      hit_info.point += offset;
      hit_info.SetFaceNormal(moved_ray, hit_info.normal);

      return true;
    }

    bool Translate::CalculateBoundingBox(double t0, double t1, BoundingBox& out) const
    {
      if (!hittable->CalculateBoundingBox(t0, t1, out))
      {
        return false;
      }

      out = BoundingBox(out.From() + offset, out.To() + offset);
      return true;
    }
  }
}
