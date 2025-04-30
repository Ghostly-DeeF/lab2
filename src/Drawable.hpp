#ifndef SGE_DRAWABLE_HPP_
#define SGE_DRAWABLE_HPP_

#include <memory>
#include "sge/2dprimitives.hpp"
#include "sge/Logger.hpp"

namespace sge
{

    void draw(const object::Line&);
    void draw(const object::Vertex&);

    class Drawable
    {
    public:
        template<typename T>
        explicit Drawable(T& object) : m_self(std::make_unique<DrawableObject<T>>(object)) {}
        Drawable(const Drawable& x) : m_self(x.m_self->copy_()) {}
        Drawable(Drawable&&) noexcept = default;
        Drawable &operator=(Drawable x) noexcept
        {
            m_self = std::move(x.m_self);
            return *this;
        }

        friend void draw(const Drawable &x)
        {
            x.m_self->draw_();
        }

    private:
        struct IDrawable
        {
            virtual ~IDrawable() = default;
            virtual std::unique_ptr<IDrawable> copy_() const = 0;
            virtual void draw_() const = 0;
        };

        template<class T>
        class DrawableObject final : public IDrawable
        {
        public:
            explicit DrawableObject(T& x) : m_data(x) {}
            std::unique_ptr<IDrawable> copy_() const override
            {
                return std::make_unique<DrawableObject>(*this);
            }
            void draw_() const override;
            
        private:
            T& m_data;
        };

        std::unique_ptr<IDrawable> m_self;
    };

    template<typename T>
    void Drawable::DrawableObject<T>::draw_() const
    {
        ::sge::draw(m_data); 
    }
}

#endif
