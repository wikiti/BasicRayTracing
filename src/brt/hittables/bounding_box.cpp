#include <cmath>

#include "brt/hittables/bounding_box.hpp"

namespace BRT
{
  namespace Hittables
  {
    Point3 corner_from;
    Point3 corner_to;

    BoundingBox::BoundingBox()
    {}

    BoundingBox::BoundingBox(const Point3& corner_from, const Point3& corner_to) :
      from(corner_from), to(corner_to)
    {}

    Point3 BoundingBox::From() const
    {
      return from;
    }

    Point3 BoundingBox::To() const
    {
      return to;
    }

    bool BoundingBox::Hit(const Ray& ray, double tmin, double tmax) const
    {
      // Check if colliding planes (X,Y,Z) overlap
      for (int axis = 0; axis < 3; ++axis)
      {
        auto inverseDirection = 1.0f / ray.Direction()[axis];
        auto t0 = (From()[axis] - ray.Origin()[axis]) * inverseDirection;
        auto t1 = (To()[axis] - ray.Origin()[axis]) * inverseDirection;

        if (inverseDirection < 0.0f)
        {
          std::swap(t0, t1);
        }

        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;

        if (tmax <= tmin)
        {
            return false;
        }
      }

      return true;
    }
  }
}
