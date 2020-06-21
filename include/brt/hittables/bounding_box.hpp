#pragma once

#include "brt/point3.hpp"
#include "brt/ray.hpp"

namespace BRT
{
  namespace Hittables
  {
    class BoundingBox
    {
      private:

        Point3 from;
        Point3 to;

      public:

        BoundingBox();
        BoundingBox(const Point3& corner_from, const Point3& corner_to);

        Point3 From() const;
        Point3 To() const;

        bool Hit(const Ray& ray, double tmin, double tmax) const;

        static BoundingBox Surrounding(const BoundingBox& a, const BoundingBox& b);
    };
  }
}
