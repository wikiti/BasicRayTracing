#include "brt/materials/lambertian.hpp"
#include "brt/misc/orthonormal_basis.hpp"
#include "brt/textures/solid_color.hpp"
#include "brt/utils.hpp"
#include "brt/vector3.hpp"

namespace BRT
{
  namespace Materials
  {
    Lambertian::Lambertian(std::shared_ptr<Textures::Texture> texture) : albedo(texture)
    {}

    Lambertian::Lambertian(const Color& color) : albedo(std::make_shared<Textures::SolidColor>(color))
    {}

    bool Lambertian::Scatter(const Ray& ray, const Hittables::HitInfo& hit_info, Color& attenuation, Ray& scattered,
                             double& pdf) const
    {
      Misc::OrthonormalBasis orthonormalBasis = Misc::OrthonormalBasis::BuildFromW(hit_info.normal);
      Vector3 direction = orthonormalBasis.Local(Utils::RandomCosineDirection());
      scattered = Ray(hit_info.point, direction.Normalize(), ray.Time());
      attenuation = albedo->Value(hit_info.u, hit_info.v, hit_info.point);
      pdf = Vector3::Dot(orthonormalBasis.W(), scattered.Direction()) / Utils::Pi;

      return true;
    }

    double Lambertian::ScatteringPdf(const Ray& ray, const Hittables::HitInfo& hit_info, const Ray& scattered) const
    {
      auto cosine = Vector3::Dot(hit_info.normal, scattered.Direction().Normalize());
      return cosine < 0 ? 0 : cosine / Utils::Pi;
    }
  }
}
