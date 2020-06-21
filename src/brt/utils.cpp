#include <random>

#include "brt/utils.hpp"
#include "brt/vector3.hpp"

namespace BRT
{
  const double Utils::Infinity = std::numeric_limits<double>::infinity();
  const double Utils::Pi = 3.1415926535897932385;

  double Utils::DegreesToRadians(double degrees)
  {
    return degrees * Pi / 180;
  }


  double Utils::Random()
  {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;

    return distribution(generator);
  }

  double Utils::Random(double max, double min)
  {
    return min + (max - min) * Random();
  }

  Vector3 Utils::RandomInUnitSphere()
  {
    while (true)
    {
      auto point = Vector3::Random(-1, 1);
      if (point.LengthSquared() < 1)
      {
        return point;
      }
    }
  }

  Vector3 Utils::RandomInUnitDisk()
  {
    return RandomInUnitSphere() * Vector3(1, 1, 0);
  }

  Vector3 Utils::RandomInHemisphere(const Vector3& normal)
  {
    // Generate a random unit vector; if it's the opposite direction, invert it
    auto random_unit = RandomUnitVector();
    return Vector3::Dot(random_unit, normal) > 0 ? random_unit : -random_unit;
  }

  Vector3 Utils::RandomUnitVector()
  {
    // NOTE: Very similar to RandomUnitSphere().Normalize();
    auto a = Random(0, 2 * Pi);
    auto z = Random(-1, 1);
    auto r = std::sqrt(1 - z * z);
    return Vector3(r*std::cos(a), r*std::sin(a), z);
  }

  double Utils::Clamp(double x, double min, double max)
  {
    if ( x < min)
    {
      return min;
    }
    else if (x > max)
    {
      return max;
    }

    return x;
  }

  Vector3 Utils::Clamp(Vector3 u, double min, double max)
  {
    return Vector3(Clamp(u.X(), min, max), Clamp(u.Y(), min, max), Clamp(u.Z(), min, max));
  }
}
