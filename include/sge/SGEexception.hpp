#ifndef SGE_INCLUDE_SGEEXCEPTION_HPP_
#define SGE_INCLUDE_SGEEXCEPTION_HPP_

#include <stdexcept>

namespace sge
{

    class sge_error : public std::runtime_error
    {
    public:
        sge_error(const std::string&);
        sge_error(const char*);
        sge_error(const sge_error&) noexcept;
        sge_error& operator=(const sge_error&) noexcept;
        virtual ~sge_error() = default;
    };

    

}

#endif
