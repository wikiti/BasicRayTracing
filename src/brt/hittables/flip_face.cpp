#include "brt/hittables/flip_face.hpp"

namespace BRT
{
  namespace Hittables
  {
    FlipFace::FlipFace(std::shared_ptr<Hittable> hittable) : hittable(hittable){};

    bool FlipFace::Hit(const Ray& ray, double t_min, double t_max, HitInfo& hit_info) const
    {
      if (!hittable->Hit(ray, t_min, t_max, hit_info))
      {
        return false;
      }

      hit_info.front_face = !hit_info.front_face;
      return true;
    }

    bool FlipFace::CalculateBoundingBox(double t0, double t1, BoundingBox& out) const
    {
      return hittable->CalculateBoundingBox(t0, t1, out);
    };
  }
}
