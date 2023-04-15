#include <ostream>

#include "brt/color.hpp"
#include "brt/utils.hpp"

namespace BRT {

  const Color Color::Black = Color::Black;
  const Color Color::White = Color::White;

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
    // Fix values, and gamma-correct them
    Color color = Vector3::Sqrt(Utils::Clamp(c, 0.0, 0.99));

    return out << static_cast<int>(255 * color.R()) << ' '
               << static_cast<int>(255 * color.G()) << ' '
               << static_cast<int>(255 * color.B());
  }
}
