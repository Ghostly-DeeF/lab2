#ifndef SGE_INCLUDE_APPLICATION_HPP_
#define SGE_INCLUDE_APPLICATION_HPP_

#include "../../src/sge/Window.hpp"
#include <iostream>

namespace sge {
    
    class Application
    {
    public:
        Application();
        Application(const char* title);
        Application(Application &&) noexcept;
        Application(const Application &) = delete;
        Application &operator=(Application &&) noexcept;
        Application &operator=(const Application &) = delete;
        virtual ~Application();
    
        void start();
        
    private:
        Window m_window;
        virtual void onUpdate() = 0;
        
    };
}

#endif
