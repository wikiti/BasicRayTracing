#pragma once

#include "brt/point3.hpp"

namespace BRT
{
  class MovingPoint3
  {
    protected:

      Point3 from, to;
      double time_start, time_end;

    public:

      MovingPoint3(const Point3& from, const Point3& to, double time_start, double time_end);

      Point3 At(double time) const;
  };
}
