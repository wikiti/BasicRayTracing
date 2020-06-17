#pragma once

#include <mutex>
#include <ostream>
#include <string>

namespace BRT
{
  class Progress
  {
    private:

      std::ostream& ostream;
      std::string label;
      int max;
      int current;

      std::mutex mutex;
      bool finished;

    public:

      Progress(std::ostream& ostream, int max);

      int Percentage();
      void Update(int new_value);
      void Increment(int by = 1);

    private:

      void SetValue(int);
  };
}
