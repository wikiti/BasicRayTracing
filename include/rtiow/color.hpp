#pragma once

#include <ostream>

#include "rtiow/vector3.hpp"

namespace RayTracingInOneWeekend
{
  class Color : public Vector3
  {
    using Vector3::Vector3;

    public:

      double R() const;
      double G() const;
      double B() const;

      friend std::ostream& operator<<(std::ostream&, const Color&);
  };
}
