#include "ShaderProgram.hpp"

#include "sge/Logger.hpp"
#include "sge/SGEexception.hpp"

#include <fstream>

#include <stdexcept>

namespace sge::rendering
{

    ShaderProgram::ShaderProgram(const char* path_vert, const char* path_frag)
    {
        std::string vert_source = "";
        std::string frag_source = "";

        vert_source = getStrFromFile("/home/jumbo/Projects/C_projects/Test_OpeGL_Engine/external/sge/res/shaders/2d/basic.vert");
        frag_source = getStrFromFile("/home/jumbo/Projects/C_projects/Test_OpeGL_Engine/external/sge/res/shaders/2d/basic.frag");

        //log::info("%s", vert_source.c_str());
        //log::info("%s", frag_source.c_str());
        
        m_vertex_id = createShader(GL_VERTEX_SHADER, vert_source.c_str());
        m_fragment_id = createShader(GL_FRAGMENT_SHADER, frag_source.c_str());
         
        m_program_id = glCreateProgram();
        glAttachShader(m_program_id, m_vertex_id);
        glAttachShader(m_program_id, m_fragment_id);
        glLinkProgram(m_program_id);
        GLint success = GL_FALSE;
        glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            throw errors::glsl_link_error("Failed to link shader", m_program_id);
        }    


        glDeleteShader(m_vertex_id);
        glDeleteShader(m_fragment_id);
    }
    
    std::string ShaderProgram::getStrFromFile(const char* path) const
    {
        std::ifstream file;
        file.open(path);
        if(!file.is_open())
        {
            log::error("Shader file open failture. path: %s", path);
            return "";
        }

        std::string line = "";
        std::string data = "";
    
        while (std::getline(file, line))
        {
            data += (line + '\n');
        }
        file.close();
        return data;
    }

    GLuint ShaderProgram::createShader(GLenum shader_type, const char* source)
    {
        GLuint shader_id = glCreateShader(shader_type);
        glShaderSource(shader_id, 1, &source, NULL);
        glCompileShader(shader_id);
        
        GLint success = GL_FALSE;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            throw errors::glsl_compile_error("Failed to compile shader", shader_id);
        }
        
        return shader_id;
    }

    void ShaderProgram::use() const
    {
        glUseProgram(m_program_id);
    }

    



}
