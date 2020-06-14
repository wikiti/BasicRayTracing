#pragma once

#include <memory>

#include "brt/hittable.hpp"
#include "brt/materials/material.hpp"
#include "brt/point3.hpp"

namespace BRT
{
  class Sphere: public Hittable
  {
    public:

      Sphere();
      Sphere(Point3, double, std::shared_ptr<Materials::Material>);

      Point3 Center() const;
      double Radius() const;

      virtual bool Hit(const Ray&, double t_min, double t_max, HitInfo&) const;
    
    private:

      bool TryHit(const Ray&, double t, double t_min, double t_max, HitInfo&) const;

    private:

      Point3 center;
      double radius;
      std::shared_ptr<Materials::Material> material_ptr;

  };
}
