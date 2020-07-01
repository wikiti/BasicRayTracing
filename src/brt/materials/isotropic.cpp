#include "brt/materials/isotropic.hpp"
#include "brt/utils.hpp"

namespace BRT
{
  namespace Materials
  {
    Isotropic::Isotropic(std::shared_ptr<Textures::Texture> albedo) : albedo(albedo)
    {}

    bool Isotropic::Scatter(const Ray& ray, const Hittables::HitInfo& hit_info, Color& attenuation,
      Ray& scattered) const
    {
      scattered = Ray(hit_info.point, Utils::RandomInUnitSphere(), ray.Time());
      attenuation = albedo->Value(hit_info.u, hit_info.v, hit_info.point);
      return true;
    }
  }
}
