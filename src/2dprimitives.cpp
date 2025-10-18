#include "sge/2dprimitives.hpp"

#include "sge/Logger.hpp"

namespace sge::geometry::objects2D
{
    math::vec3 Vertex::move(math::vec3 delta_pos)
    {
        x += delta_pos.x;
        y += delta_pos.y;
        z += delta_pos.z;
        return {x, y, z};
    }

    math::vec3 VertexColorable::move(math::vec3 delta_pos)
    {
        x += delta_pos.x;
        y += delta_pos.y;
        z += delta_pos.z;
        return {x, y, z};
    }

    std::pair<math::vec3, math::vec3> Line::move(math::vec3 delta_pos)
    {
        start.move(delta_pos);
        end.move(delta_pos);
        return std::pair{math::vec3{start.x, start.y, start.z}, math::vec3{end.x, end.y, end.z}};
    }
}
