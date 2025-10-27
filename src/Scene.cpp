#include "Scene.hpp"

#include "Window.hpp"

#include <stdexcept>

namespace sge
{
    Scene::Scene()
    {
        log::constructor("Scene");
    }

    Scene::Scene(Scene && moved) : m_shaderManager(std::move(moved.m_shaderManager)), m_objects(std::move(moved.m_objects))
    {
        log::constructor("Scene move");
    }

    Scene &Scene::operator=(Scene && moved)
    {
        log::info("Scene operator move");
        if(&moved == this)
            return *this;

        m_shaderManager = std::move(moved.m_shaderManager);
        m_objects = std::move(moved.m_objects);
        return *this;
    } 

    void Scene::rendering() const
    {
        log::lifeTime log("SCENE", "Render");
        
        auto callRenderingObject = [this](auto& object) { return object->rendering(m_windowsWidth, m_windowHeight); };
        for(const auto &object : m_objects)
        {
            std::visit(callRenderingObject, object);  
        }

        log::trace("Count %d", m_objects.size());
    }

    void Scene::setWindowSize(std::size_t windows_width, std::size_t window_height)
    {
        m_windowsWidth = windows_width;
        m_windowHeight = window_height;
    }

    void Scene::removeObject(size_t index)
    {
        if(index >= m_objects.size())
            throw errors::out_of_range("Attempt to delete a non-existent object", index, 0, m_objects.size());
        m_objects.erase(m_objects.begin() + index);
    }

    size_t Scene::countObjects() const
    {
        return m_objects.size();
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
