#ifndef SGE_SCENE_HPP_
#define SGE_SCENE_HPP_

#include "Drawable.hpp"
#include "ShaderManager.hpp"
#include "Window.hpp"

#include <string_view>
#include <vector>

#include "sge/Logger.hpp"

namespace sge
{

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
        std::vector<Drawable> m_objects;
    };


    template<typename T>
    T* Scene::add(const T& object, std::string_view shader_name)
    {
        log::lifeTime log("OBJECT", "Add");
        log::trace("Scene add %d", m_window.getWidth());
        m_objects.emplace_back(object, m_shaderManager.at(shader_name));
        return m_objects.back().getGeometry<T>();
    }

    template<typename T>
    T* Scene::get(size_t pos)
    {
        return m_objects.at(pos).getGeometry<T>();
    }

    

}

#endif
