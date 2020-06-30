#include <cmath>

#include "brt/hittables/rotate.hpp"
#include "brt/utils.hpp"

namespace BRT
{
  namespace Hittables
  {
    template <Misc::Axis A>
    Rotate<A>::Rotate()
    {}

    template <Misc::Axis A>
    Rotate<A>::Rotate(std::shared_ptr<Hittable> hittable, double angle) : hittable(hittable)
    {
      auto radians = Utils::DegreesToRadians(angle);
      sin_theta = std::sin(radians);
      cos_theta = std::cos(radians);

      PrecalculateBoundingBox();
    }

    template <Misc::Axis A>
    bool Rotate<A>::Hit(const Ray& ray, double t_min, double t_max, HitInfo& hit_info) const
    {
      auto origin = NewPosition(ray.Origin(), true);
      auto direction = NewPosition(ray.Direction(), true);

      Ray rotated_ray(origin, direction, ray.Time());

      if (!hittable->Hit(rotated_ray, t_min, t_max, hit_info))
      {
        return false;
      }

      hit_info.point = NewPosition(hit_info.point);
      hit_info.SetFaceNormal(rotated_ray, NewPosition(hit_info.normal));

      return true;
    }

    template <Misc::Axis A>
    bool Rotate<A>::CalculateBoundingBox(double t0, double t1, BoundingBox& out) const
    {
      out = bounding_box;
      return has_box;
    }

    template <Misc::Axis A>
    void Rotate<A>::PrecalculateBoundingBox()
    {
      // TODO: Decouple hard-coded times
      has_box = hittable->CalculateBoundingBox(0.0, 1.0, bounding_box);

      Point3 from(Utils::Infinity, Utils::Infinity, Utils::Infinity);
      Point3 to(Utils::NegativeInfinity, Utils::NegativeInfinity, Utils::NegativeInfinity);

      for (int i = 0; i < 2; ++i)
      {
        for (int j = 0; j < 2; ++j)
        {
          for (int k = 0; k < 2; ++k)
          {
            auto x = i * bounding_box.To().X() + (1 - i) * bounding_box.From().X();
            auto y = j * bounding_box.To().Y() + (1 - j) * bounding_box.From().Y();
            auto z = k * bounding_box.To().Z() + (1 - k) * bounding_box.From().Z();

            Vector3 new_position = NewPosition(x, y, z);

            from[Misc::Axis::X] = std::fmin(from[Misc::Axis::X], new_position[Misc::Axis::X]);
            to[Misc::Axis::X] = std::fmax(to[Misc::Axis::X], new_position[Misc::Axis::X]);

            from[Misc::Axis::Y] = std::fmin(from[Misc::Axis::Y], new_position[Misc::Axis::Y]);
            to[Misc::Axis::Y] = std::fmax(to[Misc::Axis::Y], new_position[Misc::Axis::Y]);

            from[Misc::Axis::Z] = std::fmin(from[Misc::Axis::Z], new_position[Misc::Axis::Z]);
            to[Misc::Axis::Z] = std::fmax(to[Misc::Axis::Z], new_position[Misc::Axis::Z]);
          }
        }
      }

      bounding_box = BoundingBox(from, to);
    }
  
    template <Misc::Axis A>
    Vector3 Rotate<A>::NewPosition(double x, double y, double z, bool invert) const
    {
      double signed_sin_theta = (invert ? -1.0 : 1.0) * sin_theta;

      switch (A)
      {
        case Misc::Axis::X:
          return Vector3(
            x,
            cos_theta * y - signed_sin_theta * z,
            signed_sin_theta * y + cos_theta * z
          );

        case Misc::Axis::Y:
          return Vector3(
            cos_theta * x + signed_sin_theta * z,
            y,
            -signed_sin_theta * x + cos_theta * z
          );

        default:
          return Vector3(
            cos_theta * x - signed_sin_theta * y,
            signed_sin_theta * x + cos_theta * y,
            z
          );
      }
    }

    template <Misc::Axis A>
    Vector3 Rotate<A>::NewPosition(const Vector3& v, bool invert) const
    {
      return NewPosition(v.X(), v.Y(), v.Z(), invert);
    }

    // NOTE: Force template specialization implementation to avoid undefined errors
    template class Rotate<Misc::Axis::X>;
    template class Rotate<Misc::Axis::Y>;
    template class Rotate<Misc::Axis::Z>;
  }
}
