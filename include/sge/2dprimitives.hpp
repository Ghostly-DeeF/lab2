#ifndef SGE_INCLUDE_2DPRIMITIVES_HPP_
#define SGE_INCLUDE_2DPRIMITIVES_HPP_

#include <glm/glm.hpp>

namespace sge::object
{

    struct Vertex
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    class Line
    {
    public:
        Vertex point1{0.0f, 0.0f, 0.0f};
        Vertex point2{.0f, .0f, .0f};
        float m_thickness = 0;

        glm::vec3 color{.0f, .0f, .0f};

        glm::vec3 move(glm::vec3);
        void rotate(float);

    private:
    };

}


#endif
