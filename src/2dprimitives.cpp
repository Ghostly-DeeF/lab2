#include "sge/2dprimitives.hpp"

#include "sge/Logger.hpp"

namespace sge::geometry::objects2D
{
    Vertex Point::move(math::vec3 delta_pos)
    {
        vertex += delta_pos;
        return vertex;
    }

    std::pair<Vertex, Vertex> Line::move(math::vec3 delta_pos)
    {
        start.vertex += delta_pos;
        end.vertex += delta_pos;
        return std::pair{start.vertex, end.vertex};
    }

    Vertex Line::moveStart(math::vec3 delta_pos)
    {
        start.vertex += delta_pos;
        return start.vertex;
    }

    Vertex Line::moveEnd(math::vec3 delta_pos)
    {
        end.vertex += delta_pos;
        return end.vertex;
    }


}
