#include "sge/SGEexception.hpp"

namespace sge
{

    sge_error::sge_error(const char* msg) noexcept :
        std::runtime_error(msg)
        {};

    sge_error::sge_error(const char* point, const char* msg) noexcept :
        std::runtime_error(msg),
        m_point(point)
        {};

    //const char* sge_error::what() const noexcept override
    //{
    //    return m_msg;
    //}

    const char* sge_error::point() const noexcept
    {
        return m_point;
    }

}
