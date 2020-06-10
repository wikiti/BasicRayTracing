#pragma once

#include "rtiow/point3.hpp"
#include "rtiow/ray.hpp"
#include "rtiow/vector3.hpp"

namespace RTIOW
{
  class HitInfo
  {
    public:

      HitInfo();
      HitInfo(const Point3, const Vector3, double);

      void SetFaceNormal(const Ray&, const Vector3&);

    public:

      Point3 point;
      Vector3 normal;
      double distance;
      bool front_face;
  };
}
