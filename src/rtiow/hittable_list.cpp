#include "rtiow/hittable_list.hpp"

namespace RTIOW
{
  HittableList::HittableList()
  {}

  HittableList::HittableList(std::shared_ptr<Hittable> item)
  {
    Add(item);
  }

  void HittableList::Clear()
  {
    items.clear();
  }

  void HittableList::Add(std::shared_ptr<Hittable> item)
  {
    items.push_back(item);
  }

  bool HittableList::Hit(const Ray& ray, double t_min, double t_max, HitInfo& hit_info) const
  {
    HitInfo temp_hit_info;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& item : items)
    {
      if (item->Hit(ray, t_min, closest_so_far, temp_hit_info))
      {
        hit_anything = true;
        closest_so_far = temp_hit_info.distance;
        hit_info = temp_hit_info;
      }
    }

    return hit_anything;
  }
}
