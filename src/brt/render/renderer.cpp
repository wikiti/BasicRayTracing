#include <iostream>
#include <thread>

#include "brt/hittables/hit_info.hpp"
#include "brt/materials/material.hpp"
#include "brt/render/renderer.hpp"
#include "brt/utils.hpp"

namespace BRT
{
  namespace Render
  {
    // Camera camera;
    // std::shared_ptr<Hittables::Hittable> world;

    // std::queue<int> pixelQueue;
    // std::mutex pixelQueueMutex;

    Renderer::Renderer(const Camera& camera, std::shared_ptr<Hittables::Hittable> world) :
      camera(camera), world(world)
    {}

    void Renderer::Render(Image& out, int samples_per_pixel, int max_depth, int thread_count)
    {
      PreparePixelQueue(out);

      Progress progress(std::cerr, pixel_queue.size());

      std::vector<std::thread> threads(thread_count);

      for (auto& thread : threads)
      {
        thread = std::thread(
          &Renderer::RenderThread,
          this,
          std::ref(progress),
          std::ref(out),
          samples_per_pixel,
          max_depth
        );
      }

      for (auto& thread : threads)
      {
        thread.join();
      }
    }

    void Renderer::RenderThread(Progress& progress, Image& out, int samples_per_pixel,
      int max_depth)
    {
      Pixel* pixel;
      while (pixel = RequestPixel(out))
      {
        RenderPixel(out, *pixel, samples_per_pixel, max_depth);
        progress.Increment();
      }
    }

    void Renderer::PreparePixelQueue(const Image& image)
    {
      for (int i = 0; i < image.PixelCount(); ++i)
      {
        pixel_queue.push(i);
      }
    }

    Pixel* Renderer::RequestPixel(Image& image)
    {
      std::lock_guard<std::mutex> lock(pixel_queue_mutex);

      if (pixel_queue.empty())
      {
        return nullptr;
      }

      int index = pixel_queue.front();
      pixel_queue.pop();
      return &image.PixelAt(index);
    }

    void Renderer::RenderPixel(const Image& image, Pixel& pixel,
      int samples_per_pixel, int max_depth) const
    {
      Color pixel_color;

      for (int k = 0; k < samples_per_pixel; ++k)
      {
        auto u = ((double)pixel.X() + Utils::Random()) / (image.Width() - 1);
        auto v = ((double)pixel.Y() + Utils::Random()) / (image.Height() - 1);
        Ray ray = camera.GetRay(u, v);
        pixel_color += RayColor(ray, max_depth);
      }

      pixel.SetColorValue(pixel_color / samples_per_pixel);
    }

    Color Renderer::RayColor(const Ray& ray, int depth) const
    {
      if (depth <= 0)
      {
        return Color(0, 0, 0);
      }

      Hittables::HitInfo hit_info;

      if (world->Hit(ray, hit_info))
      {
        Ray scattered;
        Color attenuation;

        if (hit_info.material_ptr->Scatter(ray, hit_info, attenuation, scattered))
        {
          return attenuation * RayColor(scattered, depth - 1);
        }

        return Color(0, 0, 0);
      }

      // Render background (sky)
      auto t = 0.5 * (ray.Direction().Y() + 1.0);
      return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
  }
}
