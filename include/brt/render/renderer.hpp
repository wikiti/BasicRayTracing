#pragma once

#include <memory>
#include <mutex>
#include <queue>

#include "brt/hittables/hittable.hpp"
#include "brt/progress.hpp"
#include "brt/render/camera.hpp"
#include "brt/render/image.hpp"

namespace BRT
{
  namespace Render
  {
    class Renderer
    {
      private:

        Camera camera;
        std::shared_ptr<Hittables::Hittable> world;

        std::queue<int> pixel_queue;
        std::mutex pixel_queue_mutex;

      public:

        Renderer(const Camera& camera, std::shared_ptr<Hittables::Hittable> world);

        void Render(Image& out, int samples_per_pixel = 100, int max_depth = 50, int threads = 4);

      private:

        void RenderThread(Progress& progress, Image& out, int samples_per_pixel, int max_depth);

        void PreparePixelQueue(const Image&);
        Pixel* RequestPixel(Image& image);
        void RenderPixel(const Image& img, Pixel& p, int samples_per_pixel, int max_depth) const;

        Color RayColor(const Ray& ray, int depth) const;
    };
  }
}
