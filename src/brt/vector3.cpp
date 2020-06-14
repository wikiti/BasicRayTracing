#include <cmath>
#include <ostream>

#include "brt/color.hpp"
#include "brt/utils.hpp"
#include "brt/vector3.hpp"

namespace BRT {
  Vector3::Vector3() : components { 0, 0, 0 }
  {}

  Vector3::Vector3(double x, double y, double z) : components { x, y, z }
  {}

  const Vector3 Vector3::Zero = Vector3();
  const Vector3 Vector3::Up = Vector3(0, 1, 0);
  const Vector3 Vector3::Down = -Vector3::Up;
  const Vector3 Vector3::Forward = Vector3(0, 0, 1);
  const Vector3 Vector3::Back = -Vector3::Forward;
  const Vector3 Vector3::Right = Vector3(1, 0, 0);
  const Vector3 Vector3::Left = -Vector3::Right;

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

  Vector3 Vector3::Sqrt(const Vector3& u)
  {
    return Vector3(std::sqrt(u.X()), std::sqrt(u.Y()), std::sqrt(u.Z()));
  }
  
  Vector3 Vector3::Reflect(const Vector3& v, const Vector3& n)
  {
    return v - 2 * Dot(v, n) * n;
  }

  // NOTE: Check Snell's Law
  Vector3 Vector3::Refract(const Vector3& uv, const Vector3& normal, double refraction)
  {
    auto cos_theta = Dot(-uv, normal);
    Vector3 parallel_component = refraction * (uv + cos_theta * normal);
    Vector3 perpendicular_component = -std::sqrt(1 - parallel_component.LengthSquared()) * normal;
    return parallel_component + perpendicular_component;
  }

  Vector3 Vector3::Random()
  {
    return Vector3(Utils::Random(), Utils::Random(), Utils::Random());
  }

  Vector3 Vector3::Random(double min, double max)
  {
    return Vector3(Utils::Random(min, max), Utils::Random(min, max), Utils::Random(min, max));
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
