#ifndef SGE_DRAWABLEMANAGER_HPP_
#define SGE_DRAWABLEMANAGER_HPP_

#include "Drawable.hpp"

#include <vector>

namespace sge
{

    class DrawableManager {
    public:
        DrawableManager() = default;
        DrawableManager(DrawableManager &&);
        DrawableManager(const DrawableManager &) = default;
        DrawableManager &operator=(DrawableManager &&);
        DrawableManager &operator=(const DrawableManager &) = default;
        ~DrawableManager() = default;

        template<typename T>
        size_t add(T&);

        void rendering();

    private:
        std::vector<Drawable> m_objects;
    };


    template<typename T>
    size_t DrawableManager::add(T& object)
    {
        m_objects.emplace_back(object);
        return m_objects.size() - 1;
    }

    

}

#endif
