#ifndef SGE_WINDOW_HPP_
#define SGE_WINDOW_HPP_

#include "Events.hpp"
#include "KeyMap.hpp"
#include <string>

struct GLFWwindow;
typedef void* (* GLaddr)(const char *name);

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
        size_t getWidth() const noexcept; 
        size_t getHeight() const noexcept;
        bool isFocused() const noexcept;

        double getCursorX() const noexcept;
        double getCursorY() const noexcept;
        bool keyPress(input::Keyboard key) const;
        bool keyPress(input::Mouse key) const;
        double getScrollX() const noexcept;
        double getScrollY() const noexcept;

        void shutdown();
        bool is_shutdown() const noexcept; 
        GLaddr getGlAddressFunc();

        void setResizeCallback(const resizeCallback& resize_function);
        void setCursorCallback(const cursorCallback& cursor_function);

    
    private:
        struct WindowData
        {
            std::string title = "";
            size_t width = 0;
            size_t height = 0;
            struct cursorData
            {
                double x = .0;
                double y = .0;
            };
            cursorData cursor = {.0, .0};
            struct scrollData
            {
                double x = .0;
                double y = .0;
            };
            scrollData scroll = {.0, .0};
            bool focused = true;
            resizeCallback custom_resize_function;
            cursorCallback custom_cursor_function;
        };

        GLFWwindow* m_pWindow = nullptr;
        WindowData m_data;
        bool m_isDestroy = false; 

        static inline int m_glfwInitNum = 0;
        
        void setResizeCallback();
        void setCursorCallback();
        void setScrollCallback();
        void setFocusCallback();
    }; 
}

#endif
