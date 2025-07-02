#ifndef SGE_INCLUDE_2DPRIMITIVES_HPP_
#define SGE_INCLUDE_2DPRIMITIVES_HPP_

#include <glm/glm.hpp>

namespace sge::objects
{

    enum class ItemType
    {
        VERTEX = 3,
        NORMAL = 3,
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
        glm::vec4 color{.0f, .0f, .0f, .0f};

        glm::vec3 move(glm::vec3);

    };

    struct Line
    {
        Point start;
        Point end;

        float m_thickness = .0f;

        glm::vec3 move(glm::vec3);
        void setPos(glm::vec3);

    };

}


#endif
