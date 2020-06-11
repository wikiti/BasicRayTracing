#include "rtiow/materials/lambertian.hpp"
#include "rtiow/utils.hpp"
#include "rtiow/vector3.hpp"

namespace RTIOW
{
  namespace Materials
  {
    Lambertian::Lambertian(const Color& color) : albedo(color)
    {}

    bool Lambertian::Scatter(const Ray& ray, const HitInfo& hit_info, Color& attenuation,
                             Ray& scattered) const {

      // Vector3 scatter_direction = hit_info.normal + Utils::RandomInHemisphere();
      Vector3 scatter_direction = hit_info.normal + Utils::RandomUnitVector();
      scattered = Ray(hit_info.point, scatter_direction);
      attenuation = albedo;

      return true;
    }
  }
}
