#include "sge/SGEexception.hpp"
#include <glad/glad.h>

namespace sge::errors
{
    exception::exception(const std::string& msg) : std::runtime_error(msg) {}

    exception::exception(const char *msg) : std::runtime_error(msg) {}



    overflow_error::overflow_error(const std::string& msg, size_t overflow_size) :
            exception(msg),
            m_overflowSize(overflow_size) {}

    overflow_error::overflow_error(const char *msg, size_t overflow_size) :
            exception(msg),
            m_overflowSize(overflow_size) {}

    size_t overflow_error::size() const noexcept
    {
        return m_overflowSize;
    }


   
    glsl_error::glsl_error(const std::string& msg) : exception(msg) {}
    glsl_error::glsl_error(const char *msg) : exception(msg) {}
    const char* glsl_error::log() const noexcept { return m_log; };

    glsl_compile_error::glsl_compile_error(const std::string& msg, unsigned id) : glsl_error(msg)
    {
        glGetShaderInfoLog(id, 1024, NULL, m_log);
    }

    glsl_compile_error::glsl_compile_error(const char *msg, unsigned id) : glsl_error(msg)
    {
        glGetShaderInfoLog(id, 1024, NULL, m_log);
    }

    glsl_link_error::glsl_link_error(const std::string& msg, unsigned id) : glsl_error(msg)
    {
        glGetProgramInfoLog(id, 1024, NULL, m_log);
    }

    glsl_link_error::glsl_link_error(const char *msg, unsigned id) : glsl_error(msg)
    {
        glGetProgramInfoLog(id, 1024, NULL, m_log);
    }



    glfw_error::glfw_error(const std::string& msg) : exception(msg) {}
    glfw_error::glfw_error(const char *msg) : exception(msg) {}



    gl_error::gl_error(const std::string& msg) : exception(msg) {}
    gl_error::gl_error(const char *msg) : exception(msg) {}

    

}
