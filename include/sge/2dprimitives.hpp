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

    struct Vertex
    {
        float x;
        float y;
        float z;
        math::vec3 move(math::vec3 delta_pos);
    };

    struct VertexColorable
    {
        float x;
        float y;
        float z;
        math::vec4 color{.0f, .0f, .0f, .0f};
        math::vec3 move(math::vec3);
    };

    struct Point
    {
        VertexColorable vertex;
        unsigned size = 1;
    };

    struct Line
    {
        VertexColorable start;
        VertexColorable end;
        math::vec4 color{.0f, .0f, .0f, .0f};

        float thickness = 1.0f;

        std::pair<math::vec3, math::vec3> move(math::vec3);
    };

}


#endif
