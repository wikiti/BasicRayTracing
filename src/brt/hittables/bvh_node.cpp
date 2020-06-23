#include <algorithm>

#include "brt/hittables/bvh_node.hpp"
#include "brt/utils.hpp"

namespace BRT
{
  namespace Hittables
  {
    // Helper compare methods

    bool Compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis)
    {
      BoundingBox box_a;
      BoundingBox box_b;

      if (!a->CalculateBoundingBox(0, 0, box_a) || !b->CalculateBoundingBox(0,0, box_b))
      {
        throw "No bounding box in bvh_node constructor.";
      }

      return box_a.From()[axis] < box_b.From()[axis];
    }

    bool CompareX(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
    {
      return Compare(a, b, 0);
    }

    bool CompareY(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
    {
      return Compare(a, b, 1);
    }

    bool CompareZ(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
    {
      return Compare(a, b, 2);
    }

    // Instance method definitions

    BVHNode::BVHNode()
    {}

    BVHNode::BVHNode(HittableList& list, double t0, double t1) :
      BVHNode(list.Items(), 0, list.Size(), t0, t1)
    {}

    BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>>& items, size_t start, size_t end,
      double t0, double t1)
    {
      static bool (*comparators[])(
        const std::shared_ptr<Hittable>,
        const std::shared_ptr<Hittable>) =
      {
        CompareX,
        CompareY,
        CompareZ
      };

      // Sort elements based on a random axis
      int random_axis = Utils::Random(0, 3);

      auto comparator = comparators[random_axis];

      size_t count = end - start;

      switch (count)
      {
        case 1:
          left = right = items[start];
          break;

        case 2:
          if (comparator(items[start], items[start+1]))
          {
            left = items[start];
            right = items[start+1];
          }
          else {
            left = items[start+1];
            right = items[start];
          }

          // left = items[start];
          // right = items[start + 1];

          // if (!comparator(left, right))
          // {
          //   std::swap(left, right);
          // }

          break;

        default:
          std::sort(items.begin() + start, items.begin() + end, comparator);
          auto middle = start + count / 2;
          left = std::make_shared<BVHNode>(items, start, middle, t0, t1);
          right = std::make_shared<BVHNode>(items, middle, end, t0, t1);
      }

      BoundingBox bounding_box_left, bounding_box_right;

      if (!left->CalculateBoundingBox(t0, t1, bounding_box_left) ||
          !right->CalculateBoundingBox(t0, t1, bounding_box_right))
      {
        throw "No bounding box in bvh_node constructor.";
      }

      bounding_box = BoundingBox::Surrounding(bounding_box_left, bounding_box_right);
    }

    bool BVHNode::Hit(const Ray& ray, double t_min, double t_max, HitInfo& hit_info) const
    {
      if (!bounding_box.Hit(ray, t_min, t_max))
      {
        return false;
      }

      // Check if the ray hits any child node, and get the closest result
      bool hit_left = left->Hit(ray, t_min, t_max, hit_info);
      bool hit_right = right->Hit(ray, t_min, hit_left ? hit_info.distance : t_max, hit_info);

      return hit_left || hit_right;
    }

    bool BVHNode::CalculateBoundingBox(double t0, double t1, BoundingBox& out) const
    {
      out = bounding_box;
      return true;
    }
  }
}
