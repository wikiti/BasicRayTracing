#pragma once

#include "brt/color.hpp"
#include "brt/hittables/hit_info.hpp"
#include "brt/materials/material.hpp"
#include "brt/textures/texture.hpp"
#include "brt/ray.hpp"

namespace BRT
{
  namespace Materials
  {
    class Lambertian : public Material
    {
      private:

        std::shared_ptr<Textures::Texture> albedo;

      public:

        Lambertian(std::shared_ptr<Textures::Texture>);

        virtual bool Scatter(const Ray&, const Hittables::HitInfo&, Color&, Ray&) const;
    };
  }
}
