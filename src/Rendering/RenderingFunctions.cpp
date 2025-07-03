#include "RenderingFunctions.hpp"

#include <glad/glad.h>
#include "Buffers.hpp"

#include "../math/Linear.hpp"

#include "sge/Logger.hpp"

namespace sge::rendering
{
   
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
        //GLuint VAO = 0;
        //glGenVertexArrays(1, &VAO);
        //log::info("VAO id: %d", VAO);
	    //glGenBuffers(1, &VBO);
        
	    //glBindVertexArray(VAO);
        
        //vao.bind();

        math::vec3(.0f, .0f, .0f); 


        //buffer->bind();
        vao.push(std::move(buffer));
        //vao.setAttributes(buffer.getAttributes(0), 0);
        //vao.setAttributes(buffer.getAttributes(1), 1);
        //buffer->unbind();
        
	    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    //glBufferData(GL_ARRAY_BUFFER, sizeof(objects::Point), &point, GL_STATIC_DRAW);



	    //glEnableVertexAttribArray(0);
	    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(objects::Point), (void*)0);
	    //glEnableVertexAttribArray(1);
	    //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(objects::Point), (void*)offsetof(objects::Point, color));
    
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);
        //vao.unbind();
        return vao;
    }

    void draw(const objects::Point &point, const VertexArray &VAO, const ShaderProgram &shader)
    {
        log::lifeTime log("OBJECT", "Draw");
        log::debug("%f", point.vertex.x);


        math::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
        math::mat4 trans;
        trans = math::translate(trans, math::vec3(1.0f, 1.0f, 0.0f));

        shader.use();
        shader.setVec3f("move", point.vertex.x, point.vertex.y, point.vertex.y);
        shader.setVec4f("color", point.color);
        glPointSize(point.size);
        VAO.bind();
        glDrawArrays(GL_POINTS, 0, 1);
        VAO.unbind();
    } 
    
}
