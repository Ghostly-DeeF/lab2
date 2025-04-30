#ifndef SGE_INCLUDE_APPLICATION_HPP_
#define SGE_INCLUDE_APPLICATION_HPP_

#include "../../src/Window.hpp"
#include "../../src/DrawableManager.hpp"

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

       DrawableManager drawableObjects; 
        
    private:
        Window m_window;
        virtual void onUpdate() = 0;

        virtual void userResizeCallback(size_t width, size_t height){};
        virtual void userCursorCallback(double xpos, double ypos){};

        void setAllCallbacks();
        
    };
}

#endif
