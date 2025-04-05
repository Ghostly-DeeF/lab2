#ifndef SGE_WINDOW_HPP_
#define SGE_WINDOW_HPP_

#include "GLFW/glfw3.h"
#include <string>
#include <memory>

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
        int getWidth(); 
        int getHeight();
        void destroy();
        
    
    private:
        GLFWwindow* m_pWindow = NULL;
        std::string m_title = "";
        int m_width = 0;
        int m_height = 0;
       
        bool m_initialized = false;
        static inline int m_glfwInitNum = 0;
        static void errorCallback(int code, const char* err_str);
        const char* error_msg = NULL;
    }; 
}

#endif
