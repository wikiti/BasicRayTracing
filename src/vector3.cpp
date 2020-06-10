#include <cmath>
#include <ostream>

#include "color.hpp"
#include "vector3.hpp"

namespace RayTracingInOneWeekend {
  Vector3::Vector3() : components { 0, 0, 0 }
  {}

  Vector3::Vector3(double x, double y, double z) : components { x, y, z }
  {}

  double Vector3::X() const
  {
    return components[0];
  }

  double Vector3::Y() const
  {
    return components[1];
  }

  double Vector3::Z() const
  {
    return components[2];
  }

  Vector3 Vector3::Normalize()
  {
    return *this / Length();
  }

  Vector3 Vector3::operator-() const
  {
    return Vector3(-X(), -Y(), -Z());
  }

  double Vector3::operator[](int i) const
  {
    return components[i];
  }

  double& Vector3::operator[](int i)
  {
    return components[i];
  }

  Vector3& Vector3::operator+=(const Vector3 other)
  {
    components[0] += other.components[0];
    components[1] += other.components[1];
    components[2] += other.components[2];
    return *this;
  }

  Vector3& Vector3::operator*=(const double t)
  {
    components[0] *= t;
    components[1] *= t;
    components[2] *= t;
    return *this;
  }

  Vector3& Vector3::operator/=(const double t)
  {
    return (*this *= 1 / t);
  }

  double Vector3::Length() const
  {
    return std::sqrt(LengthSquared());
  }

  double Vector3::LengthSquared() const
  {
    return X() * X() + Y() * Y() + Z() * Z();
  }

  Vector3::operator Color() const
  {
    return Color(X(), Y(), Z());
  }

  double Vector3::Dot(const Vector3& u, const Vector3& v)
  {
    return u.X() * v.X() + u.Y() * v.Y() + u.Z() * v.Z();
  }

  Vector3 Vector3::Cross(const Vector3& u, const Vector3& v)
  {
    return Vector3(
      u.Y() * v.Z() - u.Z() * v.Y(),
      u.Z() * v.X() - u.X() * v.Z(),
      u.X() * v.Y() - u.Y() * v.X()
    );
  }

  std::ostream& operator<<(std::ostream& out, const Vector3& v)
  {
    return out << v.X() << ' ' << v.Y() << ' ' << v.Z();
  }

  Vector3 operator+(const Vector3& u, const Vector3& v)
  {
    return Vector3(u.X() + v.X(), u.Y() + v.Y(), u.Z() + v.Z());
  }

  Vector3 operator+(double t, const Vector3& u)
  {
    return Vector3(u.X() + t, u.Y() + t, u.Z() + t);
  }

  Vector3 operator+(const Vector3& u, double t)
  {
    return t + u;
  }

  Vector3 operator-(const Vector3& u, const Vector3& v)
  {
    return Vector3(u.X() - v.X(), u.Y() - v.Y(), u.Z() - v.Z());
  }

  Vector3 operator*(const Vector3& u, const Vector3& v)
  {
      return Vector3(u.X() * v.X(), u.Y() * v.Y(), u.Z() * v.Z());
  }

  Vector3 operator*(double t, const Vector3& v)
  {
      return Vector3(t * v.X(), t * v.Y(), t * v.Z());
  }

  Vector3 operator*(const Vector3& v, double t)
  {
      return t * v;
  }

  Vector3 operator/(const Vector3& v, double t)
  {
      return (1 / t) * v;
  }
}
