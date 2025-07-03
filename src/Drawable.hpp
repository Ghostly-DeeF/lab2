#ifndef SGE_DRAWABLE_HPP_
#define SGE_DRAWABLE_HPP_

#include "Rendering/RenderingFunctions.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/ShaderProgram.hpp"

#include <memory>

#include "sge/Logger.hpp"

namespace sge
{

    class Drawable
    {
    public:
        template<typename T>
        Drawable(T& object, const rendering::ShaderProgram& shader);
        Drawable (Drawable &&) = default;
        Drawable(const Drawable& x) = delete;
        Drawable &operator=(Drawable &&) = default;
        Drawable &operator=(const Drawable x) = delete;
        ~Drawable();

        friend void setup_( Drawable&);
        friend void draw_(const Drawable&, size_t window_width, size_t window_height);

        unsigned id();

    private:
        struct IDrawable
        {
            virtual ~IDrawable() = default;
            //virtual std::unique_ptr<IDrawable> copy_() const = 0;
            virtual rendering::VertexArray setup_() const = 0;
            virtual void draw_(const rendering::VertexArray &VAO, const rendering::ShaderProgram &shader, size_t window_width, size_t window_height) const = 0;
        };

        template<class T>
        class DrawableObject final : public IDrawable
        {
        public:
            DrawableObject(T& x) : m_data(x) { log::constructor("DrawableObject"); }
            ~DrawableObject() override { log::destructor("DrawableObject"); }

            //std::unique_ptr<IDrawable> copy_() const override
            //{
            //    return std::make_unique<DrawableObject>(*this);
            //}

            rendering::VertexArray setup_() const override;
            void draw_(const rendering::VertexArray &VAO, const rendering::ShaderProgram &shader, size_t window_width, size_t window_height) const override;
            
        private:
            T& m_data; 
        };

        std::unique_ptr<IDrawable> m_self;
        rendering::VertexArray m_VAO;
        const rendering::ShaderProgram& m_shader;
    };

    template<typename T>
    Drawable::Drawable(T& object, const rendering::ShaderProgram& shader)
    : m_self(std::make_unique<Drawable::DrawableObject<T>>(object)), m_shader(shader)
    {
        log::constructor("Drawable");
        log::lifeTime log("DRAWABLE", "Setup to constructor");

        m_VAO = std::move(m_self->setup_());
        
        log::info("VAO in Drawable %d", m_VAO.id());
    }

    template<typename T>
    rendering::VertexArray Drawable::DrawableObject<T>::setup_() const
    {
        return ::sge::rendering::setup(m_data); 
    }

    template<typename T>
    void Drawable::DrawableObject<T>::draw_(const rendering::VertexArray &VAO, const rendering::ShaderProgram &shader, size_t window_width, size_t window_height) const
    {
        ::sge::rendering::draw(m_data, VAO, shader, window_width, window_height); 
    }

}

#endif
