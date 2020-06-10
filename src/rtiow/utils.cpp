#include <random>

#include "rtiow/utils.hpp"
#include "rtiow/vector3.hpp"

namespace RTIOW
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
