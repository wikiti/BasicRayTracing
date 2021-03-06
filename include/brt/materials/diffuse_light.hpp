#pragma once

#include <memory>

#include "brt/materials/material.hpp"
#include "brt/textures/texture.hpp"

namespace BRT
{
  namespace Materials
  {
    class DiffuseLight : public Material
    {
      private:

        std::shared_ptr<Textures::Texture> emit_texture;

      public:

        DiffuseLight(std::shared_ptr<Textures::Texture>);

        virtual bool Scatter(const Ray&, const Hittables::HitInfo&, Color&, Ray&) const;
        virtual Color Emit(double u, double v, const Point3& point) const;
    };
  }
}
