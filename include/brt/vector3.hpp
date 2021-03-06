#pragma once

#include <ostream>

namespace BRT
{
  class Color;

  class Vector3
  {
    protected:

      double components[3];

    public:

      static const Vector3 Zero;
      static const Vector3 Up;
      static const Vector3 Down;
      static const Vector3 Forward;
      static const Vector3 Back;
      static const Vector3 Right;
      static const Vector3 Left;

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
      static Vector3 Sqrt(const Vector3&);
      static Vector3 Reflect(const Vector3&, const Vector3&);
      static Vector3 Refract(const Vector3&, const Vector3&, double);

      static Vector3 Random();
      static Vector3 Random(double, double);

      friend std::ostream& operator<<(std::ostream&, const Vector3&);
      friend Vector3 operator+(const Vector3&, const Vector3&);
      friend Vector3 operator+(double, const Vector3&);
      friend Vector3 operator+(const Vector3&, double);
      friend Vector3 operator-(const Vector3&, const Vector3&);
      friend Vector3 operator-(const Vector3&, double);
      friend Vector3 operator*(const Vector3&, const Vector3&);
      friend Vector3 operator*(double, const Vector3&);
      friend Vector3 operator*(const Vector3&, double);
      friend Vector3 operator/(const Vector3& v, double t);
  };
}
