#include <cmath>

#include "brt/hittables/moving_sphere.hpp"

namespace BRT
{
  namespace Hittables
  {
    MovingSphere::MovingSphere(const MovingPoint3& moving_center, double radius,
      std::shared_ptr<Materials::Material> material_ptr) : moving_center(moving_center),
                                                           radius(radius),
                                                           material_ptr(material_ptr)
    {}

    Point3 MovingSphere::Center(double time) const
    {
      return moving_center.At(time);
    }

    double MovingSphere::Radius() const
    {
      return radius;
    }

    /**
     * See Sphere::Hit for more information.
     */
    bool MovingSphere::Hit(const Ray& ray, double t_min, double t_max, HitInfo& hit_info) const
    {
      Vector3 oc = ray.Origin() - Center(ray.Time());
      auto a = ray.Direction().LengthSquared();
      auto half_b = Vector3::Dot(oc, ray.Direction());
      auto c = Vector3::Dot(oc, oc) - radius * radius;
      auto discriminant =  half_b*half_b - a*c;

      if (discriminant < 0) 
      {
        return false;
      }

      // Check closests solution first, then the farthest
      auto root = std::sqrt(discriminant);
      return TryHit(ray, (-half_b - root) / a, t_min, t_max, hit_info) ||
        TryHit(ray, (-half_b + root) / a, t_min, t_max, hit_info);

      return false;
    }

    bool MovingSphere::TryHit(const Ray& ray, double t, double t_min, double t_max, HitInfo& hit_info) const
    {
      if (t <= t_min || t >= t_max)
      {
        return false;
      }

      hit_info.distance = t;
      hit_info.point = ray.At(hit_info.distance);
      hit_info.material_ptr = material_ptr;
      Vector3 outward_normal = (hit_info.point - Center(ray.Time())) / radius;
      hit_info.SetFaceNormal(ray, outward_normal);
      return true;
    }
  }
}
