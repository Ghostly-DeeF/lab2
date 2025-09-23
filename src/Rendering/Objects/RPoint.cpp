#include "RPoint.hpp"

#include "sge/Logger.hpp"

namespace sge::rendering::object
{

float toWinCord(float num, size_t win_size)
    {
        return (num-(win_size/2))/(win_size/2);
    }

    bool isInBounds(float value, float low, float high)
    {
        return  !(value < low) && (value <= high);
    }


    RPoint::RPoint(sge::objects::Point geometry, const ShaderProgram &shader) : m_geometry(geometry), m_shader(shader)
    {
        log::constructor("RPoint");
        log::lifeTime log("OBJECT", "Setup");
        log::debug("Object geometry %f", m_geometry.vertex.x);
        //log::debug("Object geometry ptr %f", getGeometry()->vertex.x);
        
        std::array<float, 3> cord = {.0f, .0f, .0f};

        ElementData<float, 3> vert_data(cord, static_cast<unsigned char>(objects::ItemType::VERTEX));

        auto buffer = std::make_unique<VertexBuffer>(vert_data.size());// + color_data.size());
        buffer->push(vert_data);

        log::info("VAO in Setup %d", m_VAO.id());

        m_VAO.push(std::move(buffer));
        
    }

    void RPoint::rendering(size_t window_width, size_t window_height) const
    {
        log::lifeTime log("OBJECT", "Draw");
        log::debug("Pos x %f", m_geometry.vertex.x);
        log::debug("Pos y %f", m_geometry.vertex.y);
        
        if (isInBounds(m_geometry.vertex.x, 0, window_width) && isInBounds(m_geometry.vertex.y, 0, window_height))
        {

            math::mat4 transform = 1.0f;
            transform = math::translate(transform, math::vec3(toWinCord(m_geometry.vertex.x, window_width), -toWinCord(m_geometry.vertex.y, window_height), 1 - m_geometry.vertex.z));
        
            m_shader.use();
            m_shader.setMat4f("transform", transform);
            m_shader.setVec4f("color", m_geometry.color);

            glPointSize(m_geometry.size);
            m_VAO.bind();
            glDrawArrays(GL_POINTS, 0, 1);
            m_VAO.unbind();

        } 
        
    }

    sge::objects::Point* RPoint::getGeometry()
    {
        return &m_geometry;
    }




}
