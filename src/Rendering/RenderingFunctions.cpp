#include "RenderingFunctions.hpp"

#include <glad/glad.h>
#include "Buffers.hpp"
#include "../math/Linear.hpp"

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
        //std::array<float, 4> color = {1.0f, 1.0f, 1.0f, 1.0f};

        ElementData<float, 3> vert_data(cord, static_cast<unsigned char>(objects::ItemType::VERTEX));
        //ElementData<float, 4> color_data(color, static_cast<unsigned char>(objects::ItemType::RGBA));

        //ElementData<objects::Vertex, 1> vert_data({point.vertex}, static_cast<unsigned char>(objects::ItemType::VERTEX));
        //ElementData<glm::vec4, 1> color_data({point.color}, static_cast<unsigned char>(objects::ItemType::RGBA));

        auto buffer = std::make_unique<VertexBuffer>(vert_data.size());// + color_data.size());
        buffer->push(vert_data);
        //buffer->push(color_data);

        VertexArray vao;
        log::info("VAO in Setup %d", vao.id());

        vao.push(std::move(buffer));

        return vao;
    }

    void draw(const objects::Point &point, const VertexArray &VAO, const ShaderProgram &shader, size_t window_width, size_t window_height)
    {
        log::lifeTime log("OBJECT", "Draw");
        log::debug("Win width %d", window_width);
        log::debug("Win height %d", window_height);
        log::debug("Pos x %f", point.vertex.x);
        log::debug("Pos y %f", point.vertex.y);
        
        log::debug("isInBounds %d", isInBounds(point.vertex.x, 0, window_width) && isInBounds(point.vertex.y, 0, window_height));

        if (isInBounds(point.vertex.x, 0, window_width) && isInBounds(point.vertex.y, 0, window_height))
        {

            math::mat4 transform = 1.0f;
            transform = math::translate(transform, math::vec3(toWinCord(point.vertex.x, window_width), toWinCord(point.vertex.y, window_height), point.vertex.z));
        
            shader.use();
            shader.setMat4f("transform", transform);
            shader.setVec4f("color", point.color);

            glPointSize(point.size);
            VAO.bind();
            glDrawArrays(GL_POINTS, 0, 1);
            VAO.unbind();

        }
    } 
    
}
