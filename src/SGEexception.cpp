#include "sge/SGEexception.hpp"

namespace sge
{
    sge_error::sge_error(const std::string& msg) : std::runtime_error(msg) {}
    sge_error::sge_error(const char* msg) : std::runtime_error(msg) {}
    

}
