#ifndef SGE_RENDERING_SHADERPROGRAM_HPP_
#define SGE_RENDERING_SHADERPROGRAM_HPP_

#include <glad/glad.h>
#include "../math/Linear.hpp"

#include <string_view>
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
        
        void setVec3f(std::string_view name, float x, float y, float z) const;
        void setVec3f(std::string_view name, const math::vec3 &data) const;
    
        void setVec4f(std::string_view name, float x, float y, float z, float w) const;
        void setVec4f(std::string_view name, const math::vec4 &data) const;

        void setMat4f(std::string_view name, const math::mat4 &data) const;

    
    private:

        GLuint m_vertex_id = 0;
        GLuint m_fragment_id = 0;
        GLuint m_program_id = 0;

        std::string getStrFromFile(const char* path) const;
        GLuint createShader(GLenum shader_type, const char* source);
    };
}

#endif
