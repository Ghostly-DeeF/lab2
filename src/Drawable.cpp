#include "Drawable.hpp"

#include "sge/2dprimitives.hpp"

#include "sge/Logger.hpp"

namespace sge
{
    Drawable::Drawable(const Drawable& x) :
        m_self(x.m_self->copy_()) {}  
    
    Drawable &Drawable::operator=(Drawable x) noexcept
    {
        m_self = std::move(x.m_self);
        return *this;
    }
    Drawable::~Drawable()
    {
        log::info("~Drawable");
    }


    unsigned int setup_(const Drawable &x)
    {
        return x.m_self->setup_();
    }

    void draw_(const Drawable &x, unsigned int id)
    {
        x.m_self->draw_(id);
    }
}
