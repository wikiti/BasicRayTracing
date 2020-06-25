#pragma once

#include <memory>

#include "brt/textures/texture.hpp"

namespace BRT
{
  namespace Textures
  {
    class Checker : public Texture
    {
      private:

        std::shared_ptr<Texture> odd;
        std::shared_ptr<Texture> even;
        double scale;

      public:

        Checker();
        Checker(std::shared_ptr<Texture> odd, std::shared_ptr<Texture> even, double scale = 10);

        virtual Color Value(double u, double v, const Point3& point) const;
    };
  }
}
