#pragma once

#include <ostream>

#include "brt/vector3.hpp"

namespace BRT
{
  class Color : public Vector3
  {
    using Vector3::Vector3;

    public:

      static const Color Black;
      static const Color White;

    public:

      double R() const;
      double G() const;
      double B() const;

      friend std::ostream& operator<<(std::ostream&, const Color&);
  };
}
