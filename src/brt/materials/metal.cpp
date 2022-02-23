#include "brt/materials/metal.hpp"
#include "brt/utils.hpp"
#include "brt/vector3.hpp"

namespace BRT
{
  namespace Materials
  {
    Metal::Metal(const Color& color, double fuzz) : albedo(color), fuzz(Utils::Clamp(fuzz, 0.0, 1.0))
    {}

    bool Metal::Scatter(const Ray& ray, const Hittables::HitInfo& hit_info, Color& attenuation, Ray& scattered,
                        double& pdf) const
    {
      Vector3 reflected = Vector3::Reflect(ray.Direction().Normalize(), hit_info.normal);
      scattered = Ray(hit_info.point, reflected + fuzz * Utils::RandomInUnitSphere(), ray.Time());
      attenuation = albedo;

      // If it's oriented among the normal, do not scatter the ray, since it probably reflected
      // "too much"
      return Vector3::Dot(scattered.Direction(), hit_info.normal) > 0;
    }
  }
}
