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
        Lambertian(const Color&);

        virtual bool Scatter(const Ray&, const Hittables::HitInfo&, Color&, Ray&, double&) const;
        virtual double ScatteringPdf(const Ray&, const Hittables::HitInfo&, const Ray&) const;
    };
  }
}
