#include "Scene.hpp"

namespace sge
{
    Scene::Scene(const Window &window) : m_window(window)
    {
        log::constructor("Scene");
        log::trace("Scene const %d", m_window.getWidth());
    }

    Scene::Scene(Scene && moved) : m_window(moved.m_window), m_objects(std::move(moved.m_objects)) 
    {
        log::constructor("Scene move");
    }

    Scene &Scene::operator=(Scene && moved)
    {
        log::info("Scene operator move");
        if(&moved == this)
            return *this;

        m_objects = std::move(moved.m_objects);
        return *this;
    } 

    void Scene::rendering()
    {
        log::lifeTime log("SCENE", "Render");
        
        auto callBuildHTML = [&](auto& label) { return label.rendering(m_window.getWidth(), m_window.getHeight()); };
        for(const auto &object : m_objects)
        {
            std::visit(callBuildHTML, object);
            //draw_(object, m_window.getWidth(), m_window.getHeight());    
        }

        //log::trace("Count %d", m_objects.size());
    }

    void Scene::addShadersSearchPath(std::string_view path, bool recursive = false)
    {
        m_shaderManager.addSearchPath(path, recursive);
    }

    Scene::~Scene()
    {
        log::destructor("Scene");
    }

}
