#ifndef SGE_SCENE_HPP_
#define SGE_SCENE_HPP_

#include "Rendering/Objects/Renderable.hpp"
#include "ShaderManager.hpp"

namespace sge
{
    class Window;
}

#include <string_view>
#include <vector>
#include <variant>
#include <memory>

#include "sge/Logger.hpp"

namespace sge
{

    class Scene {
    public:
        Scene(const Window &window);
        Scene(Scene &&);
        Scene(const Scene &) = delete;
        Scene &operator=(Scene &&);
        Scene &operator=(const Scene &) = delete;
        ~Scene();

        template<typename T>
        T* add(T object, std::string_view shader_name);
        
        template<typename T>
        T* get(size_t pos);

        void rendering();

        void addShadersSearchPath(std::string_view path, bool recursive);

    private:
        const Window &m_window;
        ShaderManager m_shaderManager;
        std::vector<std::variant< std::unique_ptr<rendering::object::RPoint>,
                                  std::unique_ptr<rendering::object::RLine> >> m_objects;
    };


    template<typename T>
    T* Scene::add(T object, std::string_view shader_name)
    {
        log::lifeTime log("OBJECT", "Add to scene");
        using ObjectType = typename corresponding_type<T>::type;
        m_objects.emplace_back(std::make_unique<ObjectType>(object, m_shaderManager.at(shader_name)) );
        auto callGetGeometry = [](auto& object)->void* { return static_cast<void*>(object->getGeometry()); };
        return static_cast<T*>(std::visit(callGetGeometry, m_objects.back()));
    }

    template<typename T>
    T* Scene::get(size_t pos)
    {
        auto callGetGeometry = [](auto& object)->void* { return static_cast<void*>(object->getGeometry()); };
        return static_cast<T*>(std::visit(callGetGeometry, m_objects.at(pos)));
    }

    

}

#endif
