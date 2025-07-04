#include "Drawable.hpp"

#include "sge/2dprimitives.hpp"

#include "sge/Logger.hpp"

namespace sge
{

    Drawable::~Drawable()
    {
        log::destructor("Drawable", "%d", m_VAO.id());
    }

    unsigned Drawable::id() const noexcept
    {
        return m_VAO.id();
    }

    void setup_(Drawable &x)
    {
        log::lifeTime log("DRAWABLE", "Setup_");
        x.m_VAO = std::move(x.m_self->setup_());
    }

    void draw_(const Drawable &x, size_t window_width, size_t window_height)
    {
        x.m_self->draw_(x.m_VAO, x.m_shader, window_width, window_height);
    }
}
