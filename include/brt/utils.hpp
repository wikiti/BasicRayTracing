#include <limits>

namespace BRT
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
      static int Random(int, int);
      static Vector3 RandomInUnitSphere();
      static Vector3 RandomInUnitDisk();
      static Vector3 RandomInHemisphere(const Vector3&);
      static Vector3 RandomUnitVector();

      static void SphereUV(const Vector3& point, double& u, double& v);

      static double TrilinearInterpolation(double c[2][2][2], double u, double v, double w);

      static double Clamp(double, double, double);
      static Vector3 Clamp(const Vector3&, double, double);
  };
}
