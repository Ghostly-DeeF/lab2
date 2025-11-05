#ifndef SGE_SCENE_HPP_
#define SGE_SCENE_HPP_

#include "Rendering/Objects/Renderable.hpp"
#include "ShaderManager.hpp"
#include "sge/SGEexception.hpp"

namespace sge
{
    class Window;
}

#include <string_view>
#include <vector>
#include <variant>
#include <memory>
#include <typeinfo>

#include "sge/Logger.hpp"

namespace sge
{

    class Scene {
    public:
        Scene();
        Scene(Scene &&);
        Scene(const Scene &) = delete;
        Scene &operator=(Scene &&);
        Scene &operator=(const Scene &) = delete;
        ~Scene();

        void rendering() const;
        void setWindowSize(std::size_t windows_width, std::size_t window_height);

        template<typename T>
        T* addObject(T object, std::string_view shader_name);
        template<typename T>
        T* getObject(size_t index);
        void removeObject(size_t index);
        size_t countObjects() const;

        void addShadersSearchPath(std::string_view path, bool recursive);

    private:
        ShaderManager m_shaderManager;
        std::vector<std::variant< std::unique_ptr<rendering::objects2D::RPoint>,
                                  std::unique_ptr<rendering::objects2D::RLine> >> m_objects;

        std::size_t m_windowsWidth = 0;
        std::size_t m_windowHeight = 0;
    };


    template<typename T>
    T* Scene::addObject(T object, std::string_view shader_name)
    {
        log::lifeTime log("OBJECT", "Add to scene");
        using ObjectType = typename rendering::objects::corresponding_type<T>::type;
        m_objects.emplace_back(std::make_unique<ObjectType>(object, m_shaderManager.at(shader_name)) );

        auto callGetGeometry = [](auto& object)->void* { return static_cast<void*>(object->getGeometry()); };
        return static_cast<T*>(std::visit(callGetGeometry, m_objects.back()));
    }

    template<typename T>
    T* Scene::getObject(size_t index)
    {
        if(index >= m_objects.size())
            throw errors::out_of_range("Trying to get an object", index, 0, m_objects.size());

        auto callGetGeometry = [](auto& object)->void* {
                auto geometry = object->getGeometry();

                if(typeid(T*) != typeid(geometry))
                    throw errors::type_mismatch_error("Mismatch between the expected type and the actual type", typeid(T*), typeid(geometry));
                return static_cast<void*>(geometry);
        };


        return static_cast<T*>(std::visit(callGetGeometry, m_objects.at(index)));
    }

    

}

#endif
