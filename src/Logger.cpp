#include "sge/Logger.hpp"

#include <cstdio>

namespace sge::log {

    void print(MsgTypeColor color, const char* type, const char* format, std::va_list args) noexcept
    {  
        char format_buff[1024] = {0};
        std::snprintf(format_buff, sizeof(format_buff), "[\033[1;%dm%s\033[0m]: %s\n", static_cast<int>(color), type, format);
        std::vprintf(format_buff, args);
    }

    void data(const char* format, ...) noexcept
    {
        std::va_list args;
        va_start(args, format);
        
        char format_buff[1024] = {0};
        std::snprintf(format_buff, sizeof(format_buff), "%s\n",format);
        
        std::vprintf(format_buff, args);

        va_end(args);
    }

    void fatal(const char* format, ...) noexcept
    {
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::FATAL, "==FATAL==", format, args);
    
        va_end(args);
    }

    void error(const char* format, ...) noexcept
    {
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::ERROR, "ERROR", format, args);
    
        va_end(args);
    }

    void warn(const char* format, ...) noexcept
    {
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::WARN, "WARN", format, args);
    
        va_end(args);
    } 

    void info(const char* format, ...) noexcept
    {
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::INFO, "INFO", format, args);
    
        va_end(args);
    }

    void debug(const char* format, ...) noexcept
    {
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::DEBUG, "DEBUG", format, args);
    
        va_end(args);
    }

    void trace(const char* format, ...) noexcept
    {
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::TRACE, "TRACE", format, args);
    
        va_end(args);
    }

}
