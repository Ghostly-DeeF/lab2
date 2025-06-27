#ifndef SGE_RENDERER_HPP_
#define SGE_RENDERER_HPP_

#include "Drawable.hpp"

#include <forward_list>

#include "sge/Logger.hpp"

namespace sge
{

    class Renderer {
    public:
        Renderer() = default;
        Renderer(Renderer &&);
        Renderer(const Renderer &) = default;
        Renderer &operator=(Renderer &&);
        Renderer &operator=(const Renderer &) = default;
        ~Renderer();

        template<typename T>
        void add(T&);

        void rendering();

    private:
        std::forward_list<Drawable> m_objects;
    };


    template<typename T>
    void Renderer::add(T& object)
    {
        log::lifeTime log("OBJECT", "Add");
        m_objects.emplace_front(object);
        //log::info("Objects count %d", m_objects.size());
        //log::trace("First Object VAO %d", m_objects.front().id());
        //setup_(m_objects.back());
        //log::info("Objects count after %d", m_objects.size());
    }

    

}

#endif
