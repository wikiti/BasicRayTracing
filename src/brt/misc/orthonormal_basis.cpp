#include <cmath>

#include "brt/misc/orthonormal_basis.hpp"

namespace BRT
{
  namespace Misc
  {
    OrthonormalBasis::OrthonormalBasis()
    {}

    OrthonormalBasis::OrthonormalBasis(const Vector3& u, const Vector3& v, const Vector3& w)
    {
      axis[0] = u;
      axis[1] = v;
      axis[2] = w;
    }

    Vector3 OrthonormalBasis::operator[](int i) const
    {
      return axis[i];
    }

    Vector3 OrthonormalBasis::U() const
    {
      return axis[0];
    }

    Vector3 OrthonormalBasis::V() const
    {
      return axis[1];
    }

    Vector3 OrthonormalBasis::W() const
    {
      return axis[2];
    }

    Vector3 OrthonormalBasis::Local(double a, double b, double c) const
    {
      return a * U() + b * V() + c * W();
    }

    Vector3 OrthonormalBasis::Local(const Vector3& a) const
    {
      return a.X() * U() + a.Y() * V() + a.Z() * W();
    }

    OrthonormalBasis OrthonormalBasis::BuildFromW(const Vector3& n)
    {
      Vector3 w = n.Normalize();
      Vector3 a = (std::fabs(w.X()) > 0.9) ? Vector3::Up : Vector3::Right;
      Vector3 v = Vector3::Cross(w, a).Normalize();
      Vector3 u = Vector3::Cross(w, v);

      return OrthonormalBasis(u, v, w);
    };
  }
}
