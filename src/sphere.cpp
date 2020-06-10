#include <cmath>

#include "sphere.hpp"

namespace RayTracingInOneWeekend
{
  Sphere::Sphere()
  {}

  Sphere::Sphere(Point3 center, double radius) : center(center), radius(radius)
  {}

  Point3 Sphere::Center() const
  {
    return center;
  }

  double Sphere::Radius() const
  {
    return radius;
  }

  /**
   * Point: P(x,y,z), Center: C(Cx,Cy,Cz), Radius: R, Ray: Pr(t) = A + tB
   *
   * (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = R^2
   * (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = (P - C) · (P - C)
   * (P - C) · (P - C) = R^2
   * (Pr(t) - C) · (Pr(t) - C) = R^2
   * (A + tB - C) · (A + tB - C) = R^2
   * t^2(B·B) + 2tB ⋅ (A - C) + (A - C)·(A - C) - R^2 = 0
   * - a = (B·B)
   * - b = 2·(A - C)
   * - c = (A - C)·(A - C) - R^2
   */
  bool Sphere::Hit(const Ray& ray, double t_min, double t_max, HitInfo& hit_info) const
  {
    Vector3 oc = ray.Origin() - center;
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

  bool Sphere::TryHit(const Ray& ray, double t, double t_min, double t_max, HitInfo& hit_info) const
  {
    if (t <= t_min || t >= t_max)
    {
      return false;
    }

    hit_info.distance = t;
    hit_info.point = ray.At(hit_info.distance);
    Vector3 outward_normal = (hit_info.point - center) / radius;
    hit_info.SetFaceNormal(ray, outward_normal);
    return true;
  }
}