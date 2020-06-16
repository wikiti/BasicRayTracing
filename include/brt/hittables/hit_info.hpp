#pragma once

#include <memory>

#include "brt/point3.hpp"
#include "brt/ray.hpp"
#include "brt/vector3.hpp"

namespace BRT
{
  namespace Materials
  {
    class Material;
  }

  namespace Hittables
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
        std::shared_ptr<Materials::Material> material_ptr;
    };
  }
}
