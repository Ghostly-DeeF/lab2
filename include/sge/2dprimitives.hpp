#ifndef SGE_INCLUDE_2DPRIMITIVES_HPP_
#define SGE_INCLUDE_2DPRIMITIVES_HPP_

#include <../src/math/Linear.hpp>

#include <utility>

namespace sge::geometry::objects2D
{

    enum class ItemType
    {
        VERTEX = 3,
        LINE = 6,
        RGBA = 4,
        RGB = 3
    };

    using Vertex = math::vec3;

    struct Point
    {
        Vertex vertex;
        unsigned size = 1;
        math::vec4 color{.0f, .0f, .0f, .0f};

        Vertex move(math::vec3);

    };

    struct Line
    {
        Point start;
        Point end;
        math::vec4 color{.0f, .0f, .0f, .0f};

        float thickness = .0f;

        std::pair<Vertex, Vertex> move(math::vec3);
        Vertex moveStart(math::vec3);
        Vertex moveEnd(math::vec3);
    };

}


#endif
