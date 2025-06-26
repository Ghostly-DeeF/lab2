#ifndef SGE_DRAWABLE_HPP_
#define SGE_DRAWABLE_HPP_

#include <memory>
#include "Rendering/RenderingFunctions.hpp"
#include "Rendering/VertexArray.hpp"
#include "sge/Logger.hpp"

namespace sge
{

    class Drawable
    {
    public:
        template<typename T>
        explicit Drawable(T& object) : m_self(std::make_unique<DrawableObject<T>>(object)) {log::constructor("Drawable"); }
        Drawable(const Drawable& x);
        Drawable(Drawable&&) noexcept = default;
        Drawable &operator=(Drawable x) noexcept;
        ~Drawable();

        friend void setup_( Drawable&);
        friend void draw_(const Drawable&);

    private:
        struct IDrawable
        {
            virtual ~IDrawable() = default;
            virtual std::unique_ptr<IDrawable> copy_() const = 0;
            virtual rendering::VertexArray setup_() const = 0;
            virtual void draw_(const rendering::VertexArray &VAO) const = 0;
        };

        template<class T>
        class DrawableObject final : public IDrawable
        {
        public:
            explicit DrawableObject(T& x) : m_data(x) { log::constructor("DrawableObject"); }
            ~DrawableObject() override { log::destructor("DrawableObject"); }
            std::unique_ptr<IDrawable> copy_() const override
            {
                return std::make_unique<DrawableObject>(*this);
            }

            rendering::VertexArray setup_() const override;
            void draw_(const rendering::VertexArray &VAO) const override;
            
        private:
            T& m_data;
        };

        std::unique_ptr<IDrawable> m_self;
        rendering::VertexArray m_VAO;
    };

    template<typename T>
    rendering::VertexArray Drawable::DrawableObject<T>::setup_() const
    {
        return ::sge::rendering::setup(m_data); 
    }

    template<typename T>
    void Drawable::DrawableObject<T>::draw_(const rendering::VertexArray &VAO) const
    {
        ::sge::rendering::draw(m_data, VAO); 
    }

}

#endif
