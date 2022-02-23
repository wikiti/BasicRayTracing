#pragma once

#include <memory>

#include "brt/materials/material.hpp"
#include "brt/textures/texture.hpp"

namespace BRT
{
  namespace Materials
  {
    class Isotropic : public Material
    {
      private:

        std::shared_ptr<Textures::Texture> albedo;

      public:

        Isotropic(std::shared_ptr<Textures::Texture> albedo);

        virtual bool Scatter(const Ray&, const Hittables::HitInfo&, Color&, Ray&, double&) const;
    };
  }
}
