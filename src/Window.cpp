#include "Window.hpp"
#include "GLFW/glfw3.h"

#include "sge/Logger.hpp"

#include "sge/SGEexception.hpp"

namespace sge
{

    Window::Window(std::string title, size_t width, size_t height) : m_data( {std::move(title), width, height} )
    {
        log::constructor("Window: %s", m_data.title.c_str());
 
        glfwSetErrorCallback(
            [](int code, const char* err_str) {
                throw errors::glfw_error(err_str);
            }
        );

        //glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

        glfwInit();
        ++m_glfwInitNum;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); 
        try
        {
            m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);
            glfwSetInputMode(m_pWindow, GLFW_STICKY_KEYS, GLFW_TRUE); 
            glfwMakeContextCurrent(m_pWindow);

            glfwSetWindowUserPointer(m_pWindow, &m_data);
            setResizeCallback();
            setCursorCallback();
            setScrollCallback();
            setFocusCallback();

        }
        catch(...)
        {
            if (--m_glfwInitNum <= 0)
            {
                log::warn("GLFW Terminate");
                glfwTerminate();
            }
            throw;
        }
            
    }

    Window::Window(Window &&moved) noexcept
    {
        glfwDestroyWindow(m_pWindow);

        m_pWindow = moved.m_pWindow;
        m_data.title = std::move(moved.m_data.title);
        m_data.width = moved.m_data.width;
        m_data.height = moved.m_data.height;
        m_data.cursor = moved.m_data.cursor;
        m_data.custom_resize_function = moved.m_data.custom_resize_function;

        ++m_glfwInitNum;

        moved.m_pWindow = nullptr;
    }

    Window &Window::operator=(Window &&moved) noexcept
    {
        if (&moved == this)
            return *this;

        glfwDestroyWindow(m_pWindow);

        m_pWindow = moved.m_pWindow;
        m_data.title = std::move(moved.m_data.title);
        m_data.width = moved.m_data.width;
        m_data.height = moved.m_data.height;
        m_data.cursor = moved.m_data.cursor;
        m_data.custom_resize_function = moved.m_data.custom_resize_function;
 
        ++m_glfwInitNum;

        moved.m_pWindow = nullptr;
        return *this;
    }

    void Window::update()
    {
        if (m_isDestroy)
            throw errors::glfw_error("Window update failure. Window is shutdown");

        log::debug("Focus %d", glfwGetWindowAttrib(m_pWindow, GLFW_FOCUSED));
        log::debug("Foc %d", m_data.focused);
        if (m_data.focused)
        { 
            glfwSwapBuffers(m_pWindow);
            glfwPollEvents();
        }
        else
        {
            glfwWaitEvents();
        } 
    }

    void Window::setResizeCallback()
    {
        glfwSetWindowSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                if (glfwGetWindowUserPointer(pWindow) == NULL)
                    return;

                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                data.width = width;
                data.height = height;
            
                if (data.custom_resize_function)
                {
                    windowSizeData size_data{
                              static_cast<size_t>(width),
                              static_cast<size_t>(height)};

                    data.custom_resize_function(size_data);
                }
            
            }
        );
    }

    void Window::setCursorCallback()
    { 
        glfwSetCursorPosCallback(m_pWindow,
            [](GLFWwindow* pWindow, double xpos, double ypos)
            {
                if (glfwGetWindowUserPointer(pWindow) == NULL)
                    return;
            
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                data.cursor.x = xpos;
                data.cursor.y = ypos;

                if (data.custom_cursor_function)
                {
                    cursorPos cursor_data{xpos, ypos};
                    data.custom_cursor_function(cursor_data);
                }
            }
        );
    }

    void Window::setScrollCallback()
    {
        glfwSetScrollCallback(m_pWindow,
            [](GLFWwindow* pWindow, double xoffset, double yoffset)
            {
                if (glfwGetWindowUserPointer(pWindow) == NULL)
                return;
                
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                data.scroll.x = xoffset;
                data.scroll.y = yoffset;

            }     
        );
    }

    void Window::setFocusCallback()
    {
        glfwSetWindowFocusCallback(m_pWindow,
            [](GLFWwindow* pWindow, int focused)
            {
                if (glfwGetWindowUserPointer(pWindow) == NULL)
                return;
                
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                if (focused) {
                    data.focused = true;
                } else {
                    data.focused = false;
                }
            }
        );
    }

    bool Window::is_active() const noexcept
    {
        return m_pWindow != nullptr? !glfwWindowShouldClose(m_pWindow) : false;
    }

    size_t Window::getWidth() const noexcept
    {
        return m_data.width;
    }

    size_t Window::getHeight() const noexcept
    {
        return m_data.height;
    }

    bool Window::isFocused() const noexcept
    {
        return m_data.focused;
    }

    double Window::getCursorX() const noexcept
    {
        return m_data.cursor.x;
    }

    double Window::getCursorY() const noexcept
    {
        return m_data.cursor.y;
    }
    
    bool Window::keyPress(input::Keyboard key) const
    {
        return glfwGetKey(m_pWindow, static_cast<int>(key)) == GLFW_PRESS? true: false;
    }

    bool Window::keyPress(input::Mouse key) const
    {
        return glfwGetMouseButton(m_pWindow, static_cast<int>(key)) == GLFW_PRESS? true: false;
    }

    double Window::getScrollX() const noexcept
    {
        return m_data.scroll.x;
    }

    double Window::getScrollY() const noexcept
    {
        return m_data.scroll.y;
    }


    void Window::shutdown()
    {
        if(!m_isDestroy)
            glfwDestroyWindow(m_pWindow);
        m_isDestroy = true;
    }

    bool Window::is_shutdown() const noexcept
    {
        return m_isDestroy;
    }

    void Window::setResizeCallback(const resizeCallback& resizeFunction)
    {
        m_data.custom_resize_function = resizeFunction;
    }

    void Window::setCursorCallback(const cursorCallback& cursorFunction)
    {
        m_data.custom_cursor_function = cursorFunction;
    }

    GLaddr Window::getGlAddressFunc()
    {
        return reinterpret_cast<GLaddr>(glfwGetProcAddress); 
    }


    Window::~Window()
    {
        log::destructor("Window: %s", m_data.title.c_str());
        shutdown();
        if (--m_glfwInitNum <= 0)
        {
            log::info("GLFW Terminate");
            glfwTerminate();
        }
    }

}


