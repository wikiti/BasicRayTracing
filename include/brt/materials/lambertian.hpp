#pragma once

#include "brt/materials/material.hpp"
#include "brt/textures/texture.hpp"

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
