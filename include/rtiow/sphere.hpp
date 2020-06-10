#pragma once

#include "rtiow/hittable.hpp"
#include "rtiow/point3.hpp"

namespace RTIOW
{
  class Sphere: public Hittable
  {
    public:

      Sphere();
      Sphere(Point3, double);

      Point3 Center() const;
      double Radius() const;

      virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;
    
    private:

      bool TryHit(const Ray&, double t, double t_min, double t_max, HitInfo&) const;

    private:

      Point3 center;
      double radius;

  };
}
