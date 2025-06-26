#ifndef SGE_RENDERER_HPP_
#define SGE_RENDERER_HPP_

#include "Drawable.hpp"

#include <vector>

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
        ~Renderer() = default;

        template<typename T>
        void add(T&);

        void rendering();

    private:
        std::vector<Drawable> m_objects;
    };


    template<typename T>
    void Renderer::add(T& object)
    {
        log::lifeTime log("OBJECT", "Add");
        m_objects.emplace_back(object); 
        setup_(m_objects.back());
    }

    

}

#endif
