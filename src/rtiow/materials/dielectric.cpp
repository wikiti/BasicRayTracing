#include <cmath>

#include "rtiow/materials/dielectric.hpp"
#include "rtiow/utils.hpp"
#include "rtiow/vector3.hpp"

namespace RTIOW
{
  namespace Materials
  {
    Dielectric::Dielectric(double refraction_index) : refraction_index(refraction_index)
    {}

    bool Dielectric::Scatter(const Ray& ray, const HitInfo& hit_info, Color& attenuation,
                             Ray& scattered) const {

      attenuation = Color(1.0, 1.0, 1.0);
      double refraction = hit_info.front_face ? 1.0 / refraction_index : refraction_index;

      Vector3 before = ray.Direction().Normalize();
      // Angle between the normal and the ray before refraction
      double cos_theta = std::fmin(Vector3::Dot(-before, hit_info.normal), 1.0);
      // Trigonometrics (sin(x)^2 + cos(x)^2 = 1)
      double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

      // Must reflect
      if (refraction * sin_theta > 1.0)
      {
        Vector3 reflected = Vector3::Reflect(before, hit_info.normal);
        scattered = Ray(hit_info.point, reflected);
        return true;
      }

      // Must refract
      Vector3 refracted = Vector3::Refract(before, hit_info.normal, refraction);
      scattered = Ray(hit_info.point, refracted);
      return true;
    }
  }
}
