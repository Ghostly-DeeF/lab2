#ifndef SGE_DRAWABLE_HPP_
#define SGE_DRAWABLE_HPP_

#include <memory>
#include "Rendering/RenderingFunctions.hpp"
#include "sge/Logger.hpp"

namespace sge
{

    class Drawable
    {
    public:
        template<typename T>
        explicit Drawable(T& object) : m_self(std::make_unique<DrawableObject<T>>(object)) {log::info("Drawable"); }
        Drawable(const Drawable& x);
        Drawable(Drawable&&) noexcept = default;
        Drawable &operator=(Drawable x) noexcept;
        ~Drawable();

        friend unsigned int setup_(const Drawable&);
        friend void draw_(const Drawable&, unsigned int);

    private:
        struct IDrawable
        {
            virtual ~IDrawable() = default;
            virtual std::unique_ptr<IDrawable> copy_() const = 0;
            virtual unsigned int setup_() const = 0;
            virtual void draw_(unsigned int) const = 0;
        };

        template<class T>
        class DrawableObject final : public IDrawable
        {
        public:
            explicit DrawableObject(T& x) : m_data(x) { log::info("DrawableObject"); }
            ~DrawableObject() override { log::info("~DrawableObject"); }
            std::unique_ptr<IDrawable> copy_() const override
            {
                return std::make_unique<DrawableObject>(*this);
            }
            unsigned int setup_() const override;
            void draw_(unsigned int) const override;
            
        private:
            T& m_data;
        };

        std::unique_ptr<IDrawable> m_self;
    };

    template<typename T>
    unsigned int Drawable::DrawableObject<T>::setup_() const
    {
        return ::sge::rendering::setup(m_data); 
    }

    template<typename T>
    void Drawable::DrawableObject<T>::draw_(unsigned int id) const
    {
        ::sge::rendering::draw(m_data, id); 
    }

}

#endif
