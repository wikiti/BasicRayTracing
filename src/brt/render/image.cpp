#include <vector>

#include "brt/render/image.hpp"

namespace BRT
{
  namespace Render
  {
    Image::Image(int width, int height) : width(width), height(height)
    {
      for (int y = Height() - 1; y >= 0; --y)
      {
        for (int x = 0; x < Width(); ++x)
        {
          pixels.push_back(Pixel(Color(0, 0, 0), x, y));
        }
      }
    }

    int Image::Width() const
    {
      return width;
    }

    int Image::Height() const
    {
      return height;
    }

    int Image::PixelCount() const
    {
      return Width() * Height();
    }

    Pixel& Image::PixelAt(int index)
    {
      return pixels[index];
    }

    const Pixel& Image::PixelAt(int index) const
    {
      return pixels.at(index);
    }

    std::ostream& operator<<(std::ostream& os, const Image& image)
    {
      os << "P3" << std::endl;
      os << image.Width() << ' ' << image.Height() << ' ' << std::endl;
      os << "255" << std::endl;

      for (int i = 0; i < image.PixelCount(); ++i)
      {
        os << image.PixelAt(i).ColorValue() << std::endl;
      }

      return os;
    }
  }
}
