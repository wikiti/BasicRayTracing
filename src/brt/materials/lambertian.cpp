#include "brt/materials/lambertian.hpp"
#include "brt/utils.hpp"
#include "brt/vector3.hpp"

namespace BRT
{
  namespace Materials
  {
    Lambertian::Lambertian(std::shared_ptr<Textures::Texture> texture) : albedo(texture)
    {}

    bool Lambertian::Scatter(const Ray& ray, const Hittables::HitInfo& hit_info, Color& attenuation,
      Ray& scattered) const
    {
      // Vector3 scatter_direction = hit_info.normal + Utils::RandomInHemisphere();
      Vector3 scatter_direction = hit_info.normal + Utils::RandomUnitVector();
      scattered = Ray(hit_info.point, scatter_direction, ray.Time());
      attenuation = albedo->Value(hit_info.u, hit_info.v, hit_info.point);

      return true;
    }
  }
}
