#include "sge/2dprimitives.hpp"

#include "sge/Logger.hpp"

namespace sge::objects
{
    math::vec3 Point::move(math::vec3 delta_pos)
    {
        vertex.x += delta_pos.x;
        vertex.y += delta_pos.y;
        vertex.z += delta_pos.z;
        return {vertex.x, vertex.y, vertex.z};
    }

}
