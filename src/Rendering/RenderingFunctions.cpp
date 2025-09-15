#include "RenderingFunctions.hpp"

#include <glad/glad.h>
#include "Buffers.hpp"
#include "../math/Linear.hpp"

#include <cmath>

#include "sge/Logger.hpp"

namespace sge::rendering
{

    float toWinCord(float num, size_t win_size)
    {
        return (num-(win_size/2))/(win_size/2);
    }

    bool isInBounds(float value, float low, float high)
    {
        return  !(value < low) && (value <= high);
    }
   
    VertexArray setup(const objects::Point &point)
    {
        log::lifeTime log("OBJECT", "Setup");

        std::array<float, 3> cord = {.0f, .0f, .0f};

        ElementData<float, 3> vert_data(cord, static_cast<unsigned char>(objects::ItemType::VERTEX));

        auto buffer = std::make_unique<VertexBuffer>(vert_data.size());// + color_data.size());
        buffer->push(vert_data);

        VertexArray vao;
        log::info("VAO in Setup %d", vao.id());

        vao.push(std::move(buffer));

        return vao;
    }

    void draw(const objects::Point &point, const VertexArray &VAO, const ShaderProgram &shader, size_t window_width, size_t window_height)
    {
        log::lifeTime log("OBJECT", "Draw");
        log::debug("Pos x %f", point.vertex.x);
        log::debug("Pos y %f", point.vertex.y);
        
        if (isInBounds(point.vertex.x, 0, window_width) && isInBounds(point.vertex.y, 0, window_height))
        {

            math::mat4 transform = 1.0f;
            transform = math::translate(transform, math::vec3(toWinCord(point.vertex.x, window_width), -toWinCord(point.vertex.y, window_height), 1 - point.vertex.z));
        
            shader.use();
            shader.setMat4f("transform", transform);
            shader.setVec4f("color", point.color);

            glPointSize(point.size);
            VAO.bind();
            glDrawArrays(GL_POINTS, 0, 1);
            VAO.unbind();

        }
    }

    
    VertexArray setup(const objects::Line& line)
    {
        std::array<float, 6> cord = {.0f, .0f, .0f, 1.f, .0f, .0f};
        std::array<float, 8> colors = { line.start.color.r,
                                        line.start.color.g,
                                        line.start.color.b,
                                        line.start.color.a,
                                        line.end.color.r,
                                        line.end.color.g,
                                        line.end.color.b,
                                        line.end.color.a};

        ElementData<float, 6> vert_data(cord, static_cast<unsigned char>(objects::ItemType::VERTEX));
        ElementData<float, 8> color_data(colors, static_cast<unsigned char>(objects::ItemType::RGBA));

        
        auto buffer = std::make_unique<VertexBuffer>(vert_data.size() + color_data.size());
        buffer->push(vert_data);
        buffer->push(color_data);


        VertexArray vao;
        log::info("VAO in Setup %d", vao.id());

        vao.push(std::move(buffer));

        return vao;
    }
    
    void draw(const objects::Line &line, const VertexArray &VAO, const ShaderProgram &shader, size_t window_width, size_t window_height)

    {
        log::lifeTime log("OBJECT", "Draw");
        
        if ((isInBounds(line.start.vertex.x, 0, window_width) &&
             isInBounds(line.start.vertex.y, 0, window_height)) ||
            (isInBounds(line.end.vertex.x, 0, window_width) &&
             isInBounds(line.end.vertex.y, 0, window_height)))
        {

            float start_x_win = toWinCord(line.start.vertex.x, window_width);
            float start_y_win = toWinCord(line.start.vertex.y, window_height);
            float end_x_win = toWinCord(line.end.vertex.x, window_width);
            float end_y_win = toWinCord(line.end.vertex.y, window_height);

            
            float scale_x = sqrt(pow(end_x_win - start_x_win, 2) + pow(end_y_win - start_y_win, 2));
            float z_angle = atan2( (end_x_win - start_x_win), (end_y_win - start_y_win)) - M_PI/2;

            log::info("Scale %f", scale_x);

            math::mat4 transform = 1.0f;
            transform = math::translate(transform, math::vec3(start_x_win, -start_y_win, 1 - line.start.vertex.z));

            transform = glm::rotate(transform, z_angle, glm::vec3(.0f, .0f, 1.0f));
            transform = glm::scale(transform, glm::vec3(scale_x, .0f, .0f));  
        
            shader.use();
            shader.setMat4f("transform", transform);
            shader.setVec4f("color", line.color);

            glLineWidth(line.thickness);
            VAO.bind();
            glDrawArrays(GL_LINE_STRIP, 0, 2);
            VAO.unbind();

        }

    }
    
}
