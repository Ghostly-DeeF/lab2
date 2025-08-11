#ifndef SGE_RENDERER_HPP_
#define SGE_RENDERER_HPP_

#include "Drawable.hpp"
#include "ShaderManager.hpp"
#include "Window.hpp"

#include <string_view>
#include <vector>

#include "sge/Logger.hpp"

namespace sge
{

    class Renderer {
    public:
        Renderer(const Window &window);
        Renderer(Renderer &&);
        Renderer(const Renderer &) = default;
        Renderer &operator=(Renderer &&);
        Renderer &operator=(const Renderer &) = default;
        ~Renderer();

        template<typename T>
        T* add(const T& object, std::string_view shader_name);
        
        template<typename T>
        T* get(size_t pos);

        void rendering();

        void addShadersSearchPath(std::string_view path);
        void addShadersSearchPath(std::string_view path, bool recursive);

    private:
        const Window &m_window;
        ShaderManager m_shaderManager;
        std::vector<Drawable> m_objects;
    };


    template<typename T>
    T* Renderer::add(const T& object, std::string_view shader_name)
    {
        log::lifeTime log("OBJECT", "Add");
        log::trace("Renderer add %d", m_window.getWidth());
        m_objects.emplace_back(object, m_shaderManager.at(shader_name));
        return m_objects.back().getGeometry<T>();
    }

    template<typename T>
    T* Renderer::get(size_t pos)
    {
        return m_objects.at(pos).getGeometry<T>();
    }

    

}

#endif
