#ifndef SGE_INCLUDE_LOGGER_HPP_
#define SGE_INCLUDE_LOGGER_HPP_

#include <cstdarg>

namespace sge::log {
    enum class MsgTypeColor
    {
        FATAL = 91,
        ERROR = 31,
        WARN = 33,
        INFO = 36,
        DEBUG = 32,
        TRACE = 35,
        CLASS = 34
        
    };
    
    void print(MsgTypeColor color, const char* type, const char* format, std::va_list args) noexcept;

    void data(const char* format, ...) noexcept;

    void fatal(const char* format, ...) noexcept;
    void error(const char* format, ...) noexcept;
    void warn(const char* format, ...) noexcept;
    void info(const char* format, ...) noexcept;
    void debug(const char* format, ...) noexcept;
    void trace(const char* format, ...) noexcept;

    void constructor(const char* class_name, const char* format, ...) noexcept;
    void constructor(const char* class_name) noexcept;

    void destructor(const char* class_name, const char* format, ...) noexcept;
    void destructor(const char* class_name) noexcept;
     
    
    class lifeTime {
    public:
        lifeTime(const char* type, const char* name);
        lifeTime(lifeTime &&) = delete;
        lifeTime(const lifeTime &) = delete;
        lifeTime &operator=(lifeTime &&) = delete;
        lifeTime &operator=(const lifeTime &) = delete;
        ~lifeTime();

        static int getCount();
    private:
        const char* m_type;
        const char* m_name;
        inline static int count = 0;
    };

}

#endif
