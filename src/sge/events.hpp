#ifndef SGE_EVENTS_HPP_
#define SGE_EVENTS_HPP_

#include <functional>

struct windowSizeData
{
    size_t width = 0;
    size_t height = 0;
};

struct cursorPos
{
    double x = 0;
    double y = 0;
};

using resizeCallback = std::function<void(const windowSizeData&)>; 
using cursorCallback = std::function<void(const cursorPos&)>; 

#endif
