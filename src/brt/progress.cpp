#include "brt/progress.hpp"

namespace BRT
{
  Progress::Progress(std::ostream& os, int m) : ostream(os), max(m), current(0),
    label("Progress: "), finished(false)
  {}

  void Progress::Update(int new_value)
  {
    std::lock_guard<std::mutex> lock(mutex);
    SetValue(new_value);
  }

  void Progress::Increment(int by)
  {
    std::lock_guard<std::mutex> lock(mutex);
    SetValue(current + by);
  }

  void Progress::SetValue(int new_value)
  {
    current = new_value;

    ostream << "\r" << label << Percentage() << "% (" << current << '/' << max << ')' << std::flush;

    if (current >= max && !finished)
    {
      finished = true;
      ostream << std::endl;
    }
  }

  int Progress::Percentage() const
  {
    return (100 * current) / max;
  }
}
