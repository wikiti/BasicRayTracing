#pragma once

#include "brt/vector3.hpp"

namespace BRT
{
  namespace Misc
  {
    class OrthonormalBasis {
      public:
        OrthonormalBasis();
        OrthonormalBasis(const Vector3& u, const Vector3& v, const Vector3& w);

        Vector3 operator[](int i) const;

        Vector3 U() const;
        Vector3 V() const;
        Vector3 W() const;

        Vector3 Local(double a, double b, double c) const;
        Vector3 Local(const Vector3& a) const;

        static OrthonormalBasis BuildFromW(const Vector3&);

      private:
          Vector3 axis[3];
  };
  }
}
