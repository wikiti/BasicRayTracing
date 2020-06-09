#include <ostream>

#include "color.hpp"

namespace RayTracingInOneWeekend {
  double Color::R() const
  {
    return X();
  }

  double Color::G() const
  {
    return Y();
  }

  double Color::B() const
  {
    return Z();
  }

  std::ostream& operator<<(std::ostream& out, const Color& c)
  {
    return out << static_cast<int>(255.999 * c.R()) << ' '
               << static_cast<int>(255.999 * c.G()) << ' '
               << static_cast<int>(255.999 * c.B());
  }
}
