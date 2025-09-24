#ifndef SGE_SRC_MATH_BASE_HPP_
#define SGE_SRC_MATH_BASE_HPP_

#include <cstddef>

namespace sge::math
{
    bool isInBounds(float value, float low, float high);
    float toOtherCord(float val, size_t max_new_val);
}

#endif
