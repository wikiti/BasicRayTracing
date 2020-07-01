#include <cmath>

#include "brt/hittables/constant_density_medium.hpp"
#include "brt/utils.hpp"

namespace BRT
{
  namespace Hittables
  {
    ConstantDensityMedium::ConstantDensityMedium(std::shared_ptr<Hittable> boundary, double density,
      std::shared_ptr<Materials::Material> phase_function) :
      boundary(boundary), density(density), phase_function(phase_function)
    {}

    bool ConstantDensityMedium::Hit(const Ray& ray, double t_min, double t_max,
      HitInfo& hit_info) const
    {
      HitInfo hit_info1, hit_info2;

      if (!boundary->Hit(ray, Utils::NegativeInfinity, Utils::Infinity, hit_info1))
      {
        return false;
      }

      if (!boundary->Hit(ray, hit_info1.distance + Utils::Epsilon, Utils::Infinity, hit_info2))
      {
        return false;
      }

      hit_info1.distance = Utils::Clamp(hit_info1.distance, t_min, Utils::Infinity);
      hit_info2.distance = Utils::Clamp(hit_info2.distance, Utils::NegativeInfinity, t_max);

      if (hit_info1.distance >= hit_info2.distance)
      {
        return false;
      }

      hit_info1.distance = Utils::Clamp(hit_info1.distance, 0.0, Utils::Infinity);

      const auto ray_length = ray.Direction().Length();
      const auto distance_inside_boundary = (hit_info2.distance - hit_info1.distance) * ray_length;
      const auto hit_distance = (-1.0 / density) * std::log(Utils::Random());

      if (hit_distance > distance_inside_boundary)
      {
        return false;
      }

      hit_info.distance = hit_info1.distance + hit_distance / ray_length;
      hit_info.point = ray.At(hit_info.distance);
      hit_info.normal = Vector3::Forward; // arbitrary
      hit_info.front_face = true; // arbitrary
      hit_info.material = phase_function;

      return true;
    }

    bool ConstantDensityMedium::CalculateBoundingBox(double t0, double t1, BoundingBox& out) const
    {
      return boundary->CalculateBoundingBox(t0, t1, out);
    }
  }
}
