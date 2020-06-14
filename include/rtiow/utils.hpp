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
      static Vector3 RandomInUnitSphere();
      static Vector3 RandomInUnitDisk();
      static Vector3 RandomInHemisphere(const Vector3&);
      static Vector3 RandomUnitVector();

      static double Clamp(double, double, double);
      static Vector3 Clamp(Vector3, double, double);
  };
}
