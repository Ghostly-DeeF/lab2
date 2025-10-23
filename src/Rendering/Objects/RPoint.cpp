#include "RPoint.hpp"

#include <glad/glad.h>

#include "../../math/Base.hpp"
#include "../Buffers.hpp"
#include "../../Data.hpp"

#include "sge/Logger.hpp"

namespace sge::rendering::object
{

    RPoint::RPoint(sge::geometry::objects2D::Point geometry, const ShaderProgram &shader) : m_geometry(geometry), m_shader(shader)
    {
        log::constructor("RPoint");
        log::lifeTime log("OBJECT", "Setup");
        log::debug("Object geometry %f", m_geometry.vertex.x);
        
        std::array<float, 3> cord = {.0f, .0f, .0f};

        ElementData<float, 3> vert_data(cord, static_cast<unsigned char>(geometry::objects2D::ItemType::VERTEX));

        auto buffer = std::make_unique<VertexBuffer>(vert_data.size());
        buffer->push(vert_data);

        log::info("VAO in Setup %d", m_VAO.id());

        m_VAO.push(std::move(buffer));
    }

    void RPoint::rendering(size_t window_width, size_t window_height)
    {
        log::lifeTime log("POINT OBJECT", "Draw");
        log::debug("Pos x %f", m_geometry.vertex.x);
        log::debug("Pos y %f", m_geometry.vertex.y);
        //log::debug("VAO %d", m_VAO);
        
        if ( !math::isInBounds(m_geometry.vertex.x, 0, window_width) ||
             !math::isInBounds(m_geometry.vertex.y, 0, window_height) )
        return;

        if( m_geometry.vertex.x != m_oldPos.x ||
            m_geometry.vertex.y != m_oldPos.y ||
            m_geometry.vertex.z != m_oldPos.z)
        {
            m_transform = 1.0f;
            m_transform = math::translate(m_transform, math::vec3(math::toOtherCord(m_geometry.vertex.x, window_width), -math::toOtherCord(m_geometry.vertex.y, window_height), 1 - m_geometry.vertex.z));
            m_oldPos = {m_geometry.vertex.x, m_geometry.vertex.y, m_geometry.vertex.z};
        }

        m_shader.use();
        m_shader.setMat4f("transform", m_transform);
        m_shader.setVec4f("color", m_geometry.vertex.color);
        glPointSize(m_geometry.size);
        m_VAO.bind();
        glDrawArrays(GL_POINTS, 0, 1);
        m_VAO.unbind();
    }

    sge::geometry::objects2D::Point* RPoint::getGeometry()
    {
        return &m_geometry;
    }




}
