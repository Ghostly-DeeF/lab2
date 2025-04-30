#ifndef SGE_INCLUDE_SGEEXCEPTION_HPP_
#define SGE_INCLUDE_SGEEXCEPTION_HPP_

#include <stdexcept>

namespace sge
{

    class sge_error : public std::runtime_error
    {
    public:
        explicit sge_error(const char*) noexcept;
        sge_error(const char*, const char*) noexcept;
        //sge_error(sge_error &&) = default;
        //sge_error(const sge_error &) = default;
        //sge_error &operator=(sge_error &&) = default;
        //sge_error &operator=(const sge_error &) = default;
        //~sge_error() = default;

        const char* point() const noexcept;

    private:
        
        const char* m_point = {0};

    };

}

#endif
