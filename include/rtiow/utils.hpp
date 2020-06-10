#include <limits>

namespace RTIOW
{
  class Vector3;

  class Utils
  {
    public:

      static const double Infinity;
      static const double Pi;

      static double DegreesToRadians(double);

      static double Random();
      static double Random(double, double);

      static double Clamp(double, double, double);
      static Vector3 Clamp(Vector3, double, double);
  };
}
