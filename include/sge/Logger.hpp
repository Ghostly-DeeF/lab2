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
        
    };
    
    void print(MsgTypeColor color, const char* type, const char* format, std::va_list args) noexcept;

    void data(const char* format, ...) noexcept;

    void fatal(const char* format, ...) noexcept;
    void error(const char* format, ...) noexcept;
    void warn(const char* format, ...) noexcept;
    void info(const char* format, ...) noexcept;
    void debug(const char* format, ...) noexcept;
    void trace(const char* format, ...) noexcept;

}

#endif
