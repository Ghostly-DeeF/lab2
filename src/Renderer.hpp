#ifndef SGE_RENDERER_HPP_
#define SGE_RENDERER_HPP_

#include "Drawable.hpp"
#include "ShaderManager.hpp"
#include "Window.hpp"

#include <string_view>
#include <forward_list>

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
        void add(const T& object, std::string_view shader_name);

        void rendering();

    private:
        const Window &m_window;
        ShaderManager shaderManager;
        std::forward_list<Drawable> m_objects;
    };


    template<typename T>
    void Renderer::add(const T& object, std::string_view shader_name)
    {
        log::lifeTime log("OBJECT", "Add");
        log::trace("Renderer add %d", m_window.getWidth());
        m_objects.emplace_front(object, shaderManager.at(shader_name));
        log::trace("Renderer add %d", m_window.getWidth());
        //log::info("Objects count %d", m_objects.size());
        //log::trace("First Object VAO %d", m_objects.front().id());
        //setup_(m_objects.back());
        //log::info("Objects count after %d", m_objects.size());
    }

    

}

#endif
