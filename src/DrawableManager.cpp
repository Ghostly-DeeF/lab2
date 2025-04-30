#include "DrawableManager.hpp"

namespace sge
{

    DrawableManager::DrawableManager(DrawableManager && moved) : m_objects(std::move(moved.m_objects)) {}

    DrawableManager &DrawableManager::operator=(DrawableManager && moved)
    {
        if(&moved == this)
            return *this;

        m_objects = std::move(moved.m_objects);
        return *this;
    }

    void DrawableManager::rendering()
    {
        for(const auto &object : m_objects)
        {
            draw(object);    
        }
    }

}
