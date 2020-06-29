#include "brt/materials/diffuse_light.hpp"

namespace BRT
{
  namespace Materials
  {
    DiffuseLight::DiffuseLight(std::shared_ptr<Textures::Texture> texture) : emit_texture(texture)
    {}

    bool DiffuseLight::Scatter(const Ray& ray, const Hittables::HitInfo& hit_info, Color& attenuation,
      Ray& scattered) const
    {
      return false;
    }

    Color DiffuseLight::Emit(double u, double v, const Point3& point) const
    {
      return emit_texture->Value(u, v, point);
    }
  }
}
