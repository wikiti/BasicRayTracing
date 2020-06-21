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
      for (int plane = 0; plane < 3; ++plane)
      {
        auto t0 = std::fmin((from[plane] - ray.Origin()[plane]) / ray.Direction()[plane],
                            (to[plane] - ray.Origin()[plane]) / ray.Direction()[plane]);
        auto t1 = std::fmax((from[plane] - ray.Origin()[plane]) / ray.Direction()[plane],
                            (to[plane] - ray.Origin()[plane]) / ray.Direction()[plane]);

        tmin = std::fmax(t0, tmin);
        tmax = std::fmin(t1, tmax);

        if (tmax <= tmin)
        {
          return false;
        }
      }

      return true;
    }
  }
}
