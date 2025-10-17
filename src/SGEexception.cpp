#include "sge/SGEexception.hpp"
#include <glad/glad.h>
#include <cstring>

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

    size_t overflow_error::size() const noexcept { return m_overflowSize; }


   
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



    gl_error::gl_error(unsigned severity, unsigned id, unsigned type, unsigned source, const char *msg) : exception(msg), m_severity(severity), m_id(id), m_type(type), m_source(source) {}

    const char* gl_error::severity() const noexcept
    {
        switch (m_severity)
        {
            case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
            case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
            case GL_DEBUG_SEVERITY_LOW: return "LOW";
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
            default: return "";
        }
    }

    unsigned gl_error::id() const noexcept { return m_id; }

    const char* gl_error::type() const noexcept
    {
        switch (m_type)
        {
            case GL_DEBUG_TYPE_ERROR:               return "Error";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behaviour";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "Undefined Behaviour"; 
            case GL_DEBUG_TYPE_PORTABILITY:         return "Portability";
            case GL_DEBUG_TYPE_PERFORMANCE:         return "Performance";
            case GL_DEBUG_TYPE_MARKER:              return "Marker";
            case GL_DEBUG_TYPE_PUSH_GROUP:          return "Push Group";
            case GL_DEBUG_TYPE_POP_GROUP:           return "Pop Group";
            case GL_DEBUG_TYPE_OTHER:               return "Other";
            default: return "";
        }
    }

    const char* gl_error::source() const noexcept
    {
        switch (m_source)
        {
            case GL_DEBUG_SOURCE_API:             return "OpenGL API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "Window System";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
            case GL_DEBUG_SOURCE_THIRD_PARTY:     return "Third Party";
            case GL_DEBUG_SOURCE_APPLICATION:     return "Application";
            case GL_DEBUG_SOURCE_OTHER:           return "Other";
            default: return "";
        }
    }


    shader_error::shader_error(const std::string& msg) : exception(msg) {}
    shader_error::shader_error(const char* msg) : exception(msg) {}

        shader_not_loaded::shader_not_loaded(const std::string& msg, std::string_view name) : shader_error(msg), m_name(name) {}
    shader_not_loaded::shader_not_loaded(const char* msg, std::string_view name) : shader_error(msg), m_name(name) {}
    const char* shader_not_loaded::name() const noexcept
    {
        return m_name.data();
    }

    shader_not_found::shader_not_found(const std::string& msg, const std::string_view path) : shader_error(msg)
    {
        std::strcpy(m_path, path.data());
    }
    shader_not_found::shader_not_found(const char* msg, const std::string_view path) : shader_error(msg)
    {
        std::strcpy(m_path, path.data());
    }
    const char* shader_not_found::path() const noexcept
    {
        return m_path;
    }


    out_of_range::out_of_range(const std::string& msg, int index, int lower, int upper) : exception(msg), m_index(index), m_lower(lower), m_upper(upper) {}

    out_of_range::out_of_range(const char* msg, int index, int lower, int upper) : exception(msg), m_index(index), m_lower(lower), m_upper(upper) {}  

    int out_of_range::index() const noexcept
    {
        return m_index;
    }

    int out_of_range::lower() const noexcept
    {
        return m_lower;
    }

    int out_of_range::upper() const noexcept
    {
        return m_upper;
    }

    
    type_mismatch_error::type_mismatch_error(const std::string& msg, const std::type_info& first_type, const std::type_info& second_type) : exception(msg), m_first_type(first_type), m_second_type(second_type) {}

    type_mismatch_error::type_mismatch_error(const char *msg, const std::type_info& first_type, const std::type_info& second_type) : exception(msg), m_first_type(first_type), m_second_type(second_type) {}

    const std::type_info& type_mismatch_error::getFirstType() const noexcept
    {
        return m_first_type;
    }

    const std::type_info& type_mismatch_error::getSecondType() const noexcept
    {
        return m_second_type;
    }



}
