#include "sge/Logger.hpp"

#include <cstdio>
#include <cstring>
#include <algorithm>

const unsigned MAX_INDENT = 12;
const unsigned INDENT = 2;


namespace sge::log {

    void print(MsgTypeColor color, const char* type, const char* format, std::va_list args, unsigned offset) noexcept
    {
        char indent[MAX_INDENT + 1] = {0};
        std::memset(indent, ' ', std::clamp(offset*INDENT, 0u, MAX_INDENT));
        indent[std::clamp(offset*INDENT, 0u, MAX_INDENT)] = '\0';

        char format_buff[1024] = {0};
        std::snprintf(format_buff, sizeof(format_buff), "%s[\033[1;%dm%s\033[0m]: %s\n", indent, static_cast<int>(color), type, format);
        std::vprintf(format_buff, args);
    }

    void print(MsgTypeColor color, const char* type, const char* format, int offset) noexcept
    {
        char indent[13] = {0};
        std::memset(indent, ' ', (offset*2<=12)?(offset*2):(12));
        indent[(offset*2<=12)?(offset*2):(12)] = '\0';

        std::printf("%s[\033[1;%dm%s\033[0m]: %s\n", indent, static_cast<int>(color), type, format);
    }







    void data(const char* format, ...) noexcept
    {
        #if(defined LOG_ALL || defined LOG_DATA)
        std::va_list args;
        va_start(args, format);
       
        char indent[MAX_INDENT + 1] = {0};
        std::memset(indent, ' ', std::clamp(lifeTime::getCount()*INDENT, 0u, MAX_INDENT));
        indent[std::clamp(lifeTime::getCount()*INDENT, 0u, MAX_INDENT)] = '\0';

        char format_buff[1024] = {0};
        std::snprintf(format_buff, sizeof(format_buff), "%s%s\n", indent, format);
        
        std::vprintf(format_buff, args);

        va_end(args);
        #endif
    }

    void fatal(const char* format, ...) noexcept
    {
        #if(defined LOG_ALL || defined LOG_FATAL || defined LOG_EXCEPTIONS)
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::FATAL, "==FATAL==", format, args, lifeTime::getCount());
    
        va_end(args);
        #endif
    }

    void error(const char* format, ...) noexcept
    {
        #if(defined LOG_ALL || defined LOG_ERROR || defined LOG_EXCEPTIONS)
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::ERROR, "ERROR", format, args, lifeTime::getCount());
    
        va_end(args);
        #endif
    }

    void warn(const char* format, ...) noexcept
    {
        #if(defined LOG_ALL || defined LOG_WARN || defined LOG_EXCEPTIONS)
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::WARN, "WARN", format, args, lifeTime::getCount());
    
        va_end(args);
        #endif
    } 

    void info(const char* format, ...) noexcept
    {
        #if(defined LOG_ALL || defined LOG_INFO)
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::INFO, "INFO", format, args, lifeTime::getCount());
    
        va_end(args);
        #endif
    }

    void debug(const char* format, ...) noexcept
    {
        #if(defined LOG_ALL || defined LOG_DEBUG)
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::DEBUG, "DEBUG", format, args, lifeTime::getCount());
    
        va_end(args);
        #endif
    }

    void trace(const char* format, ...) noexcept
    {
        #if(defined LOG_ALL || defined LOG_TRACE)
        std::va_list args;
        va_start(args, format);

        print(MsgTypeColor::TRACE, "TRACE", format, args, lifeTime::getCount());
    
        va_end(args);
        #endif
    }

    void constructor(const char* class_name, const char* format, ...) noexcept
    {
        #if(defined LOG_ALL || defined LOG_CONSTRUCTOR)
        std::va_list args;
        va_start(args, format);

        char format_buff[2048] = {0};
        std::snprintf(format_buff, sizeof(format_buff), "%s %s", class_name, format);

        print(MsgTypeColor::CLASS, "CONSTRUCTOR", format_buff, args, lifeTime::getCount());
    
        va_end(args);
        #endif
    }

    void constructor(const char* class_name) noexcept
    {
        #if(defined LOG_ALL || defined LOG_CONSTRUCTOR)
        print(MsgTypeColor::CLASS, "CONSTRUCTOR", class_name, lifeTime::getCount());
        #endif
    }


    void destructor(const char* class_name, const char* format, ...) noexcept
    {
        #if(defined LOG_ALL || defined LOG_DESTRUCTOR)
        std::va_list args;
        va_start(args, format);

        char format_buff[2048] = {0};
        std::snprintf(format_buff, sizeof(format_buff), "%s %s", class_name, format);

        print(MsgTypeColor::CLASS, "DESTRUCTOR", format_buff, args, lifeTime::getCount());
    
        va_end(args);
        #endif
    }

    void destructor(const char* class_name) noexcept
    {
        #if(defined LOG_ALL || defined LOG_DESTRUCTOR)
        print(MsgTypeColor::CLASS, "DESTRUCTOR", class_name, lifeTime::getCount());
        #endif
    }

    void opertor(const char* class_name, const char* operator_name, const char* format, ...) noexcept
    {
        #if(defined LOG_ALL || defined LOG_OPERATOR)
        std::va_list args;
        va_start(args, format);

        char format_buff[2048] = {0};
        std::snprintf(format_buff, sizeof(format_buff), "[\033[1;%dm%s\033[0m]: %s %s", static_cast<int>(MsgTypeColor::CLASS), operator_name, class_name, format);

        print(MsgTypeColor::CLASS, "OPERATOR", format_buff, args, lifeTime::getCount());
    
        va_end(args);
        #endif
    }

    void opertor(const char* class_name, const char* operator_name) noexcept
    {
        #if(defined LOG_ALL || defined LOG_OPERATOR)
        char format_buff[1028] = {0};
        std::snprintf(format_buff, sizeof(format_buff), "[\033[1;%dm%s\033[0m]: %s", static_cast<int>(MsgTypeColor::CLASS), operator_name, class_name);
        
        print(MsgTypeColor::CLASS, "OPERATOR", format_buff, lifeTime::getCount());
        #endif
    }



 
    lifeTime::lifeTime(const char* type, const char* name) : m_type(type), m_name(name)
    {
        #if(defined LOG_ALL || defined LOG_LIFETIME)
        char indent[MAX_INDENT + 1] = {0};
        std::memset(indent, ' ', std::clamp(lifeTime::getCount()*INDENT, 0u, MAX_INDENT));
        indent[std::clamp(lifeTime::getCount()*INDENT, 0u, MAX_INDENT)] = '\0';

        std::printf("%s[\033[2;36m%s\033[0m] [\033[1;32mstart\033[0m]: %s\n", indent, m_type, m_name);
        count++;
        #endif
    }
            
    lifeTime::~lifeTime()
    {
        #if(defined LOG_ALL || defined LOG_LIFETIME)
        char indent[MAX_INDENT + 1] = {0};
        std::memset(indent, ' ', std::clamp(lifeTime::getCount()*INDENT, 0u, MAX_INDENT));
        indent[std::clamp((lifeTime::getCount()-1)*INDENT, 0u, MAX_INDENT)] = '\0';
    
        std::printf("%s[\033[2;36m%s\033[0m] [\033[1;33mend\033[0m]: %s\n", indent, m_type, m_name);
        count--;
        #endif
    }

    int lifeTime::getCount()
    {
        return count;
    }




}

