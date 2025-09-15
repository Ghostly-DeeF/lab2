#ifndef SGE_INCLUDE_2DPRIMITIVES_HPP_
#define SGE_INCLUDE_2DPRIMITIVES_HPP_

#include <../src/math/Linear.hpp>

namespace sge::objects
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
        float x = .0f;
        float y = .0f;
        float z = .0f; 
    };

    struct Point
    {
        Vertex vertex;
        unsigned size = 1;
        math::vec4 color{.0f, .0f, .0f, .0f};

        math::vec3 move(math::vec3);

    };

    struct Line
    {
        Point start;
        Point end;
        math::vec4 color{.0f, .0f, .0f, .0f};

        float thickness = .0f;

        math::vec3 move(math::vec3);
        void setPos(math::vec3);

    };

}


#endif
