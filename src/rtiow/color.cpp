#include <ostream>

#include "rtiow/color.hpp"
#include "rtiow/utils.hpp"

namespace RTIOW {
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
    Color color = Utils::Clamp(c, 0, 0.99);

    return out << static_cast<int>(255 * color.R()) << ' '
               << static_cast<int>(255 * color.G()) << ' '
               << static_cast<int>(255 * color.B());
  }
}
