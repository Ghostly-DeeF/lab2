#include "Drawable.hpp"

#include "sge/2dprimitives.hpp"

#include "sge/Logger.hpp"

namespace sge
{

    
/*
    Drawable::Drawable(const Drawable& x) :
        m_self(x.m_self->copy_())
    {
        log::constructor("Drawable copy");
    }  
*/
/*
    Drawable &Drawable::operator=(Drawable x) noexcept
    {
        m_self = std::move(x.m_self);
        return *this;
    }
*/
    Drawable::~Drawable()
    {
        log::destructor("Drawable", "%d", m_VAO.id());
    }

    unsigned Drawable::id()
    {
        return m_VAO.id();
    }


    void setup_(Drawable &x)
    {
        log::lifeTime log("DRAWABLE", "Setup_");
        x.m_VAO = std::move(x.m_self->setup_());
    }

    void draw_(const Drawable &x)
    {
        x.m_self->draw_(x.m_VAO, x.m_shader);
    }
}
