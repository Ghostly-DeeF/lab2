#include "sge/Logger.hpp"

#include <cstdio>

namespace sge::log {

    void print(MsgTypeColor color, const char* type, const char* format, std::va_list args) noexcept
    {
        printf("[\033[1;%dm%s\033[0m]: ", (int)color, type);
        
        std::vprintf(format, args);
        std::printf("\n");
    }

    void data(const char* format, ...) noexcept
    {
        std::va_list args;
        va_start(args, format);

        std::vprintf(format, args);
        std::printf("\n");

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
