#include "Drawable.hpp"

#include "sge/2dprimitives.hpp"

#include "sge/Logger.hpp"

namespace sge
{

    void draw(const object::Line& line)
    {
        log::debug("%f", line.point1.x);
    }

    void draw(const object::Vertex& vert)
    {
        log::debug("Vertex %f", vert.x);
    }
  
}
