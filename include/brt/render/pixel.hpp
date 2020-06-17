#pragma once

#include "brt/color.hpp"

namespace BRT
{
  namespace Render
  {
    class Pixel
    {
      private:

        Color color;
        int x, y;

      public:

        Pixel(const Color&, int, int);

        int X() const;
        int Y() const;
        const Color& ColorValue() const;

        void SetColorValue(const Color&);
    };
  }
}
