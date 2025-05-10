#include "Renderer.hpp"

namespace sge
{

    Renderer::Renderer(Renderer && moved) : m_objects(std::move(moved.m_objects)) {}

    Renderer &Renderer::operator=(Renderer && moved)
    {
        if(&moved == this)
            return *this;

        m_objects = std::move(moved.m_objects);
        return *this;
    }

    void Renderer::rendering()
    {
        for(const auto &object : m_objects)
        {
            draw_(object, 1);    
        }
    }

}
