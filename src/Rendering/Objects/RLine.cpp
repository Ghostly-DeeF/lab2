#include "RLine.hpp"

#include <glad/glad.h>

#include "../../math/Base.hpp"
#include "../Buffers.hpp"
#include "../../Data.hpp"

#include "sge/Logger.hpp"


namespace sge::rendering::object
{

    RLine::RLine(sge::geometry::objects2D::Line geometry, const ShaderProgram &shader) : m_geometry(geometry), m_shader(shader)
    {
        std::array<float, 6> cord = {.0f, .0f, .0f, 1.f, .0f, .0f};
        std::array<float, 8> colors = { m_geometry.start.color.r,
                                        m_geometry.start.color.g,
                                        m_geometry.start.color.b,
                                        m_geometry.start.color.a,
                                        m_geometry.end.color.r,
                                        m_geometry.end.color.g,
                                        m_geometry.end.color.b,
                                        m_geometry.end.color.a};

        ElementData<float, 6> vert_data(cord, static_cast<unsigned char>(geometry::objects2D::ItemType::VERTEX));
        ElementData<float, 8> color_data(colors, static_cast<unsigned char>(geometry::objects2D::ItemType::RGBA));

        
        auto buffer = std::make_unique<VertexBuffer>(vert_data.size() + color_data.size());
        buffer->push(vert_data);
        buffer->push(color_data);


        log::info("VAO in Setup %d", m_VAO.id());

        m_VAO.push(std::move(buffer));
    }

    void RLine::rendering(size_t window_width, size_t window_height)
    {
        log::lifeTime log("OBJECT", "Draw");
        
        if ((math::isInBounds(m_geometry.start.vertex.x, 0, window_width) &&
             math::isInBounds(m_geometry.start.vertex.y, 0, window_height)) ||
            (math::isInBounds(m_geometry.end.vertex.x, 0, window_width) &&
             math::isInBounds(m_geometry.end.vertex.y, 0, window_height)))
        {

            float start_x_win = math::toOtherCord(m_geometry.start.vertex.x, window_width);
            float start_y_win = math::toOtherCord(m_geometry.start.vertex.y, window_height);
            float end_x_win = math::toOtherCord(m_geometry.end.vertex.x, window_width);
            float end_y_win = math::toOtherCord(m_geometry.end.vertex.y, window_height);

            
            float scale_x = sqrt(pow(end_x_win - start_x_win, 2) + pow(end_y_win - start_y_win, 2));
            float z_angle = atan2( (end_x_win - start_x_win), (end_y_win - start_y_win)) - M_PI/2;

            math::mat4 transform = 1.0f;
            transform = math::translate(transform, math::vec3(start_x_win, -start_y_win, 1 - m_geometry.start.vertex.z));

            transform = glm::rotate(transform, z_angle, glm::vec3(.0f, .0f, 1.0f));
            transform = glm::scale(transform, glm::vec3(scale_x, .0f, .0f));  
        
            m_shader.use();
            m_shader.setMat4f("transform", transform);
            m_shader.setVec4f("color", m_geometry.color);

            glLineWidth(m_geometry.thickness);
            m_VAO.bind();
            glDrawArrays(GL_LINE_STRIP, 0, 2);
            m_VAO.unbind();

        }
    }

    sge::geometry::objects2D::Line* RLine::getGeometry()
    {
        return &m_geometry;
    }

}
