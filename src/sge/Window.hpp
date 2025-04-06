#ifndef SGE_WINDOW_HPP_
#define SGE_WINDOW_HPP_

#include "GLFW/glfw3.h"
#include "events.hpp"
#include <string>

namespace sge
{
    class Window
    {
    public:
        Window(std::string title, size_t width, size_t height);
        Window(Window &&) noexcept;
        Window(const Window &) = delete;
        Window &operator=(Window &&) noexcept;
        Window &operator=(const Window &) = delete;
        ~Window();

        void update();
        bool is_active() const noexcept;
        int getWidth() const noexcept; 
        int getHeight() const noexcept;
        void destroy();

        void setResizeCallback(const resizeCallback& resize_function);
        
    
    private:
        struct WindowData
        {
            std::string title = "";
            size_t width = 0;
            size_t height = 0;
            resizeCallback custom_resize_function;
        };

        GLFWwindow* m_pWindow = nullptr;
        WindowData m_data;
        bool m_initialized = false;
        const char* error_msg = NULL;

        static inline int m_glfwInitNum = 0;

    }; 
}

#endif
