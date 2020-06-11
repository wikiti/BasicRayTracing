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

      double refraction = hit_info.front_face ? 1.0 / refraction_index : refraction_index;

      Vector3 before = ray.Direction().Normalize();
      Vector3 refracted = Vector3::Refract(before, hit_info.normal, refraction);

      attenuation = Color(1.0, 1.0, 1.0);
      scattered = Ray(hit_info.point, refracted);

      return true;
    }
  }
}
