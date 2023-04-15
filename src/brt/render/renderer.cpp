#include <cmath>
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
    Renderer::Renderer(const Camera& camera, std::shared_ptr<Hittables::Hittable> world, const Color& background)
        : camera(camera), world(world), background(background)
    {}

    void Renderer::Render(Image& out, int samples_per_pixel, int max_depth, int thread_count)
    {
      PreparePixelQueue(out);

      Progress progress(std::cerr, pixel_queue.size());

      std::vector<std::thread> threads(thread_count);

      for (auto& thread : threads)
      {
        thread =
            std::thread(&Renderer::RenderThread, this, std::ref(progress), std::ref(out), samples_per_pixel, max_depth);
      }

      for (auto& thread : threads)
      {
        thread.join();
      }
    }

    void Renderer::RenderThread(Progress& progress, Image& out, int samples_per_pixel, int max_depth)
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

    void Renderer::RenderPixel(const Image& image, Pixel& pixel, int samples_per_pixel, int max_depth) const
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

      if (!world->Hit(ray, hit_info))
      {
        return background;
      }

      Ray scattered;
      Color attenuation; // Not currently used
      Color emitted = hit_info.material->Emit(hit_info.u, hit_info.v, hit_info.point);
      double pdf;
      Color albedo;

      if (!hit_info.material->Scatter(ray, hit_info, albedo, scattered, pdf))
      {
        return emitted;
      }

      Point3 on_light = Point3(Utils::Random(213, 343), 554, Utils::Random(227, 332));
      Point3 to_light = on_light - hit_info.point;
      double distance_squared = to_light.LengthSquared();
      to_light = to_light.Normalize();

      if (Vector3::Dot(to_light, hit_info.normal) < 0)
      {
        return emitted;
      }

      double light_area = (343-213)*(332-227);
      auto light_cosine = std::fabs(to_light.Y());

      if (light_cosine < 0.000001)
      {
          return emitted;
      }

      pdf = distance_squared / (light_cosine * light_area);
      scattered = Ray(hit_info.point, to_light, ray.Time());

      return emitted +
             albedo * hit_info.material->ScatteringPdf(ray, hit_info, scattered) * RayColor(scattered, depth - 1) / pdf;
    }
  }
}
