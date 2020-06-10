#include "rtiow/utils.hpp"

namespace RTIOW
{
  const double Utils::Infinity = std::numeric_limits<double>::infinity();
  const double Utils::Pi = 3.1415926535897932385;

  double Utils::DegreesToRadians(double degrees)
  {
    return degrees * Pi / 180;
  }
}
