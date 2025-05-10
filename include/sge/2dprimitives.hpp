#ifndef SGE_INCLUDE_2DPRIMITIVES_HPP_
#define SGE_INCLUDE_2DPRIMITIVES_HPP_

#include <glm/glm.hpp>

#include "../../src/Data.hpp"

namespace sge::objects
{

    enum class ItemType
    {
        VERTEX = 3,
        RGBA = 4
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
        glm::vec4 color{.0f, .0f, .0f, .0f};

        glm::vec3 move(glm::vec3);

        ElementData<Vertex, 1> getVerteces() const;
        ElementData<glm::vec4, 1> getColor() const;
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
