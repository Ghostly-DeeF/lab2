#include "Drawable.hpp"

#include "sge/2dprimitives.hpp"

#include "sge/Logger.hpp"

namespace sge
{

    Drawable::~Drawable()
    {
        log::destructor("Drawable", "%d", m_VAO.id());
    }

    void setup_(Drawable &obj)
    {
        log::lifeTime log("DRAWABLE", "Setup_");
        obj.m_VAO = std::move(obj.m_object->setup_());
    }

    void draw_(const Drawable &obj, size_t window_width, size_t window_height)
    {
        obj.m_object->draw_(obj.m_VAO, obj.m_shader, window_width, window_height);
    }
}
