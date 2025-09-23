#ifndef SGE_SCENE_HPP_
#define SGE_SCENE_HPP_

#include "Rendering/Objects/Renderable.hpp"
#include "ShaderManager.hpp"
#include "Window.hpp"

#include <string_view>
#include <vector>
#include <variant>

#include "sge/Logger.hpp"

namespace sge
{

    template<typename T> struct corresponding_type;
    template<> struct corresponding_type<sge::objects::Point> { using type = sge::rendering::object::RPoint; };

    class Scene {
    public:
        Scene(const Window &window);
        Scene(Scene &&);
        Scene(const Scene &) = default;
        Scene &operator=(Scene &&);
        Scene &operator=(const Scene &) = default;
        ~Scene();

        template<typename T>
        T* add(const T& object, std::string_view shader_name);
        
        template<typename T>
        T* get(size_t pos);

        void rendering();

        void addShadersSearchPath(std::string_view path, bool recursive);

    private:
        const Window &m_window;
        ShaderManager m_shaderManager;
        std::vector<std::variant<rendering::object::RPoint>> m_objects;
    };


    template<typename T>
    T* Scene::add(const T& object, std::string_view shader_name)
    {
        log::lifeTime log("OBJECT", "Add to scene");
        log::trace("Scene add %d", m_window.getWidth());
        using ObjectType = typename corresponding_type<T>::type;
        m_objects.emplace_back(ObjectType{object, m_shaderManager.at(shader_name)});
        
        log::trace("Size: %d", m_objects.size());
        auto callGetGeometry = [](auto& object) { return object.getGeometry(); };

        T* object_ptr = std::visit(callGetGeometry, m_objects.back());
        log::trace("%f", object_ptr->vertex.x);
        return object_ptr;
    }

    template<typename T>
    T* Scene::get(size_t pos)
    {
        auto callGetGeometry = [](auto& object) { return object.getGeometry(); };
        return std::visit(callGetGeometry, m_objects.at(pos));
    }

    

}

#endif
