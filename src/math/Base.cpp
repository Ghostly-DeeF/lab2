#include "Base.hpp"

namespace sge::math
{
    bool isInBounds(float value, float low, float high)
    {
        return !(value < low) && (value <= high);
    }

    float toOtherCord(float val, std::size_t max_new_val)
    {
        return (val-(max_new_val/2))/(max_new_val/2);
    }
}
