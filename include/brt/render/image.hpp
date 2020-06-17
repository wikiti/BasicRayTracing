#pragma once

#include <vector>

#include "brt/render/pixel.hpp"

namespace BRT
{
  namespace Render
  {
    class Image
    {
      private:

        int width, height;
        std::vector<Pixel> pixels;

      public:

        Image(int, int);

        int Width() const;
        int Height() const;
        int PixelCount() const;

        Pixel& PixelAt(int index);
        const Pixel& PixelAt(int index) const;

        friend std::ostream& operator<<(std::ostream&, const Image&);
    };
  }
}
