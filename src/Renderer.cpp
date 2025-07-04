#include "Renderer.hpp"

namespace sge
{
    Renderer::Renderer(const Window &window) : m_window(window)
    {
        log::constructor("Renderer");
        log::trace("Renderer const %d", m_window.getWidth());
    }

    Renderer::Renderer(Renderer && moved) : m_objects(std::move(moved.m_objects)), m_window(moved.m_window)
    {
        log::constructor("Renderer move");
    }

    Renderer &Renderer::operator=(Renderer && moved)
    {
        log::info("Renderer operator move");
        if(&moved == this)
            return *this;

        m_objects = std::move(moved.m_objects);
        return *this;
    } 

    void Renderer::rendering()
    {
        log::lifeTime log("SCENE", "Render");

        for(const auto &object : m_objects)
        { 
            draw_(object, m_window.getWidth(), m_window.getHeight());    
        }

        log::trace("Count %d", m_objects.size());
    }

    Renderer::~Renderer()
    {
        log::destructor("Renderer");
    }

}
