#include "RenderingFunctions.hpp"

#include <glad/glad.h>
#include "Buffers.hpp"

#include "sge/Logger.hpp"

namespace sge::rendering
{
   
    unsigned int setup(const objects::Point &point)
    {
        log::debug("ObjectSetup");

        GLuint VAO = 0;
        glGenVertexArrays(1, &VAO);
        log::debug("VAO id: %d", VAO);
	    //glGenBuffers(1, &VBO);
        
	    glBindVertexArray(VAO);
        
        ElementData<objects::Vertex, 1> vert_data({point.vertex}, static_cast<unsigned char>(objects::ItemType::VERTEX));
        ElementData<glm::vec4, 1> color_data({point.color}, static_cast<unsigned char>(objects::ItemType::RGBA));

        VertexBuffer buffer(vert_data.size() + color_data.size());
        buffer.push(vert_data);
        buffer.push(color_data);
        
	    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    //glBufferData(GL_ARRAY_BUFFER, sizeof(objects::Point), &point, GL_STATIC_DRAW);



	    //glEnableVertexAttribArray(0);
	    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(objects::Point), (void*)0);
	    //glEnableVertexAttribArray(1);
	    //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(objects::Point), (void*)offsetof(objects::Point, color));
    
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
 
        return VAO;
    }

    void draw(const objects::Point &point, unsigned int VAO)
    {
        log::debug("%f", point.vertex.x);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 1);
        glBindVertexArray(0);
    } 
    
}
