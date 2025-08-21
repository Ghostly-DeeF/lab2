#ifndef SGE_INCLUDE_APPLICATION_HPP_
#define SGE_INCLUDE_APPLICATION_HPP_

#include "../../src/Window.hpp"
#include "../../src/Scene.hpp"
#include "../../src/GlRender.hpp"

namespace sge
{
    
    class Application
    {
    public:
        Application();
        Application(const char* title);
        Application(const char* title, size_t width, size_t height);
        Application(Application &&) noexcept;
        Application(const Application &) = delete;
        Application &operator=(Application &&) noexcept;
        Application &operator=(const Application &) = delete;
        virtual ~Application();
    
        void start();

        void setVSync(bool status) const;

        size_t width() const noexcept;
        size_t height() const noexcept;
        bool isFocused() const noexcept;
        double getFrameTime() const noexcept;
        double getFrameRate() const noexcept;

        double cursorX() const noexcept;
        double cursorY() const noexcept;
        bool keyPress(input::Keyboard key) const;
        bool keyPress(input::Mouse key) const;
        double scrollX() const noexcept;
        double scrollY() const noexcept;

    private:
        Window m_window;
        GlRender m_render;

    public:

        Scene scene;
        
        
    private:

        double m_frameTime = .0;
        
        virtual void onUpdate() = 0;

        virtual void userResizeCallback(size_t width, size_t height) {};
        virtual void userCursorCallback(double xpos, double ypos) {};

        void setAllCallbacks();
        
    };
}

#endif
