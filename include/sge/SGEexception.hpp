#ifndef SGE_INCLUDE_SGEEXCEPTION_HPP_
#define SGE_INCLUDE_SGEEXCEPTION_HPP_

#include <stdexcept>
#include <string_view>

namespace sge::errors
{

    class exception : public std::runtime_error
    {
    public:
        exception(const std::string& msg);
        exception(const char *msg);
        exception(const exception&) noexcept;
        exception& operator=(const exception&) = default;
        ~exception() override = default;
    };



    class overflow_error : public exception
    {
    public:
        overflow_error(const std::string& msg, size_t);
        overflow_error(const char *msg, size_t);
        
        size_t size() const noexcept;

    private:
        size_t m_overflowSize = 0;
    };



    class glsl_error : public exception {
    public:
        glsl_error(const std::string& msg);
        glsl_error(const char *msg);
        
        virtual const char* log() const noexcept;

    protected:
        char m_log[1024] = {0};
    };

    class glsl_compile_error : public glsl_error
    {
    public:
        glsl_compile_error(const std::string& msg, unsigned id);
        glsl_compile_error(const char *msg, unsigned id);
    };

    class glsl_link_error : public glsl_error
    {
    public:
        glsl_link_error(const std::string& msg, unsigned id);
        glsl_link_error(const char *msg, unsigned id);
    };



    class glfw_error : public exception
    {
    public:
        glfw_error(const std::string& msg);
        glfw_error(const char *msg);
    };



    class gl_error : public exception
    {
    public:
        gl_error(unsigned severity, unsigned id, unsigned type, unsigned source, const char *msg);

        const char* severity() const noexcept;
        unsigned id() const noexcept;
        const char* type() const noexcept;
        const char* source() const noexcept;

    private:

        unsigned m_severity = 0;
        unsigned m_id = 0;
        unsigned m_type = 0;
        unsigned m_source = 0;

    };

    class shader_error : public exception
    {
    public:
        shader_error(const std::string& msg);
        shader_error(const char* msg);
    };

    class shader_not_loaded : public shader_error
    {
    public:
        shader_not_loaded(const std::string& msg, std::string_view name);
        shader_not_loaded(const char* msg, std::string_view name);
        const char* name() const noexcept;
    private:
        std::string_view m_name;
    };

    class shader_not_found : public shader_error
    {
    public:
        shader_not_found(const std::string& msg, const std::string_view path);
        shader_not_found(const char* msg, const std::string_view path);

        const char* path() const noexcept;
    private:
        char m_path[1024];
    };

    class out_of_range : public exception
    {
    public:
        out_of_range(const std::string& msg, int index, int lower, int upper);
        out_of_range(const char *msg, int index, int lower, int upper);

        int index() const noexcept;
        int lower() const noexcept;
        int upper() const noexcept;

    private:
        int m_index = 0;
        int m_lower = 0;
        int m_upper = 0;
    };


}

#endif
