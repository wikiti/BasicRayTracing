#include "rtiow/hit_info.hpp"

namespace RayTracingInOneWeekend
{
  HitInfo::HitInfo()
  {}

  HitInfo::HitInfo(const Point3 point, const Vector3 normal, double distance) :
    point(point), normal(normal), distance(distance)
  {}


  void HitInfo::SetFaceNormal(const Ray& ray, const Vector3& outward_normal)
  {
    front_face = Vector3::Dot(ray.Direction(), outward_normal) < 0;
    normal = front_face ? outward_normal :-outward_normal;
  }
}
