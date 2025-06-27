#ifndef SGE_RENDERING_SHADERPROGRAM_HPP_
#define SGE_RENDERING_SHADERPROGRAM_HPP_

#include <glad/glad.h>
#include <string>

namespace sge::rendering
{

    class ShaderProgram
    {
    public:
    
        ShaderProgram(const char* path_vert, const char* path_frag);
        ShaderProgram(ShaderProgram &&) noexcept = default;
        ShaderProgram(const ShaderProgram &) = default;
        ShaderProgram &operator=(ShaderProgram &&) noexcept = default;
        ShaderProgram &operator=(const ShaderProgram &) = default;
    
        ~ShaderProgram();

        void use() const;
    
    private:

        GLuint m_vertex_id = 0;
        GLuint m_fragment_id = 0;
        GLuint m_program_id = 0;

        std::string getStrFromFile(const char* path) const;
        GLuint createShader(GLenum shader_type, const char* source);
    };
}

#endif
