#include "brt/hittables/hittable_list.hpp"

namespace BRT
{
  namespace Hittables
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

    bool HittableList::CalculateBoundingBox(double t0, double t1, BoundingBox& out) const
    {
      if (items.empty())
      {
        return false;
      }

      BoundingBox temp;
      bool first = true;

      for (const auto& item : items)
      {
        if (!item->CalculateBoundingBox(t0, t1, temp))
        {
          return false;
        }

        out = first ? temp : BoundingBox::Surrounding(temp, out);
        first = false;
      }

      return true;
    }
  }
}
