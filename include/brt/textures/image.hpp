#pragma once

#include <string>

#include "brt/textures/texture.hpp"

namespace BRT
{
  namespace Textures
  {
    class Image : public Texture
    {
      private:

        int width;
        int height;
        int bytes_per_scanline;
        unsigned char* bytes;

      public:

        const static int BytesPerPixel;

      public:

        Image();
        Image(std::string filename);

        ~Image();

        virtual Color Value(double u, double v, const Point3& point) const;
    };
  }
}
