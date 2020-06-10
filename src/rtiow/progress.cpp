#include "rtiow/progress.hpp"

namespace RayTracingInOneWeekend
{
  Progress::Progress(std::ostream& os, int m) : ostream(os), max(m), current(0), label("Process: ")
  {}

  void Progress::update(int newValue)
  {
    current = newValue;

    ostream << "\r" << label << current << "/" << max << std::flush;
    if (current >= max) {
      ostream << std::endl;
    }
  }
}
