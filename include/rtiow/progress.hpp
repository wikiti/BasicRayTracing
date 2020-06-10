#include <ostream>
#include <string>

namespace RayTracingInOneWeekend
{
  class Progress
  {
    private:

      std::ostream& ostream;
      std::string label;
      int max;
      int current;
    
    public:

      Progress(std::ostream& ostream, int max);

      void update(int);
  };
}