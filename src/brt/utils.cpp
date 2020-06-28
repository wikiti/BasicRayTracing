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

  // Random int between [0, 1)
  double Utils::Random()
  {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;

    return distribution(generator);
  }

  // Random int between [min, max)
  double Utils::Random(double min, double max)
  {
    return min + (max - min) * Random();
  }

  // Random int between [min, max)
  int Utils::Random(int min, int max)
  {
    return static_cast<int>(min + (max - min) * Random());
  }

  Vector3 Utils::RandomInUnitSphere()
  {
    while (true)
    {
      auto point = Vector3::Random(-1.0, 1.0);
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
    auto a = Random(0.0, 2 * Pi);
    auto z = Random(-1.0, 1.0);
    auto r = std::sqrt(1 - z * z);
    return Vector3(r*std::cos(a), r*std::sin(a), z);
  }

  // https://en.wikipedia.org/wiki/UV_mapping#Finding_UV_on_a_sphere
  void Utils::SphereUV(const Vector3& point, double& u, double& v)
  {
    Vector3 d = -point;

    u = 0.5 + std::atan2(d.X(), d.Z()) / (2 * Pi);
    v = 0.5 - std::asin(d.Y()) / Pi;
  }

  double Utils::TrilinearInterpolation(double c[2][2][2], double u, double v, double w)
  {
    auto accumulator = 0.0;

    for (int i = 0; i < 2; ++i)
    {
      for (int j = 0; j < 2; ++j)
      {
        for (int k = 0; k < 2; ++k)
        {
          accumulator += (i*u + (1 - i) * (1 - u)) * (j*v + (1 - j) * (1 - v)) *
                         (k*w + (1 - k) * (1 - w)) * c[i][j][k];
        }
      }
    }

    return accumulator;
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

  Vector3 Utils::Clamp(const Vector3& u, double min, double max)
  {
    return Vector3(Clamp(u.X(), min, max), Clamp(u.Y(), min, max), Clamp(u.Z(), min, max));
  }
}
