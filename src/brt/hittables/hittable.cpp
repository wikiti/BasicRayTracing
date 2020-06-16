#include "brt/hittables/hittable.hpp"
#include "brt/utils.hpp"

namespace BRT
{
  namespace Hittables
  {
    bool Hittable::Hit(const Ray& ray, HitInfo& hit_info) const
    {
      return Hit(ray, 0.001, Utils::Infinity, hit_info);
    }
  }
}
