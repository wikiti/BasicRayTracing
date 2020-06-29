#include "brt/textures/image.hpp"
#include "brt/utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace BRT
{
  namespace Textures
  {
    const int Image::BytesPerPixel = 3;

    Image::Image() : bytes(nullptr), width(0), height(0), bytes_per_scanline(0)
    {}

    Image::Image(std::string filename)
    {
      auto components_per_pixel = BytesPerPixel;

      // Load image using STB library
      bytes = stbi_load(
        filename.c_str(),
        &width, &height,
        &components_per_pixel, components_per_pixel
      );

      if (!bytes)
      {
        throw "Could not load texture " + filename;
      }

      bytes_per_scanline = BytesPerPixel * width;
    }

    Image::~Image()
    {
      if (bytes != nullptr)
      {
        delete bytes;
      }
    }

    Color Image::Value(double u, double v, const Point3& point) const
    {
      if (bytes == nullptr)
      {
        return Color(1, 0, 1);
      }

      u = Utils::Clamp(u, 0.0, 1.0);
      v = 1.0 - Utils::Clamp(v, 0.0, 1.0);

      int i = Utils::Clamp(static_cast<int>(u * width), 0, width - 1);
      int j = Utils::Clamp(static_cast<int>(v * height), 0, height - 1);

      unsigned char* pixel = bytes + j * bytes_per_scanline + i * BytesPerPixel;

      // Normalize color scale from [0,255] to [0, 1]
      return Utils::Remap(Color(pixel[0], pixel[1], pixel[2]), 0, 255, 0, 1);
    }
  }
}
