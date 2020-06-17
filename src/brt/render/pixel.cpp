#include "brt/color.hpp"
#include "brt/render/pixel.hpp"

namespace BRT
{
  namespace Render
  {
    Pixel::Pixel(const Color& color, int x, int y) : color(color), x(x), y(y)
    {}

    int Pixel::X() const
    {
      return x;
    }

    int Pixel::Y() const
    {
      return y;
    }

    const Color& Pixel::ColorValue() const
    {
      return color;
    }

    void Pixel::SetColorValue(const Color& new_color)
    {
      color = new_color;
    }
  }
}
