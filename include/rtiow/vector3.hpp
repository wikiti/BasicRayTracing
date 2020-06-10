#pragma once

#include <ostream>

namespace RTIOW
{
  class Color;

  class Vector3
  {
    protected:

      double components[3];

    public:

      explicit Vector3();
      explicit Vector3(double, double, double);

      double X() const;
      double Y() const;
      double Z() const;

      Vector3 Normalize();

      Vector3 operator-() const;
      double operator[](int) const;
      double& operator[](int);

      Vector3& operator+=(const Vector3);
      Vector3& operator*=(const double);
      Vector3& operator/=(const double);

      double Length() const;
      double LengthSquared() const;

      operator Color() const;

      static double Dot(const Vector3&, const Vector3&);
      static Vector3 Cross(const Vector3&, const Vector3&);

      friend std::ostream& operator<<(std::ostream&, const Vector3&);
      friend Vector3 operator+(const Vector3&, const Vector3&);
      friend Vector3 operator+(double, const Vector3&);
      friend Vector3 operator+(const Vector3&, double);
      friend Vector3 operator-(const Vector3&, const Vector3&);
      friend Vector3 operator*(const Vector3&, const Vector3&);
      friend Vector3 operator*(double, const Vector3&);
      friend Vector3 operator*(const Vector3&, double);
      friend Vector3 operator/(const Vector3& v, double t);
  };
}
