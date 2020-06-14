#include "rtiow/hittable.hpp"
#include "rtiow/utils.hpp"

namespace RTIOW
{
  bool Hittable::Hit(const Ray& ray, HitInfo& hit_info) const
  {
    return Hit(ray, 0.001, Utils::Infinity, hit_info);
  }
}
