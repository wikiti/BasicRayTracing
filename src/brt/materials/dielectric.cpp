#include <cmath>

#include "brt/materials/dielectric.hpp"
#include "brt/utils.hpp"
#include "brt/vector3.hpp"

namespace BRT
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

      // Must reflect (based on solution to Snell's law of Schlick angle's aproximation)
      if (ShouldReflect(before, hit_info, refraction))
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


    bool Dielectric::ShouldReflect(const Vector3& dir, const HitInfo& hit_info,
                                   double refraction) const
    {
      // Angle between the normal and the ray before refraction
      double cos_theta = std::fmin(Vector3::Dot(-dir, hit_info.normal), 1.0);
      // Trigonometrics (sin(x)^2 + cos(x)^2 = 1)
      double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

      // Either Snell's law doesn't have a solution, or angle make the ray reflect
      return refraction * sin_theta > 1.0 || Utils::Random() < Schlick(cos_theta, refraction);
    }

    // https://en.wikipedia.org/wiki/Schlick%27s_approximation
    double Dielectric::Schlick(double cosine, double refraction) const
    {
      auto r0 = (1 - refraction) / (1 + refraction);
      r0 = r0 * r0;
      return r0 + (1 - r0) * std::pow(1 - cosine, 5);
    }
  }
}
