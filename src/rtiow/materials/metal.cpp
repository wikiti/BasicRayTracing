#include "rtiow/materials/metal.hpp"
#include "rtiow/utils.hpp"
#include "rtiow/vector3.hpp"

namespace RTIOW
{
  namespace Materials
  {
    Metal::Metal(const Color& color) : albedo(color)
    {}

    bool Metal::Scatter(const Ray& ray, const HitInfo& hit_info, Color& attenuation,
                             Ray& scattered) const {

      Vector3 reflected = Vector3::Reflect(ray.Direction().Normalize(), hit_info.normal);
      scattered = Ray(hit_info.point, reflected);
      attenuation = albedo;

      // If it's oriented among the normal, do not scatter the ray, since it probably reflected
      // "too much"
      return Vector3::Dot(scattered.Direction(), hit_info.normal) > 0;
    }
  }
}
