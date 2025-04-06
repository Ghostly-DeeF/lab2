#include "Window.hpp"
#include <stdexcept>

#include <iostream>


namespace sge
{

Window::Window(std::string title, size_t width, size_t height) : m_data( {std::move(title), width, height} )
{
    std::cout << "Window constructor\n";
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    if (glfwGetError(&error_msg))
        throw std::runtime_error(error_msg);

    glfwInit();
    if (glfwGetError(&error_msg))
        throw std::runtime_error(error_msg);
    ++m_glfwInitNum;

    m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);

    glfwSetWindowUserPointer(m_pWindow, &m_data);

    glfwMakeContextCurrent(m_pWindow);
    
    if (!glfwGetError(&error_msg))
    { 
        m_initialized = true; 
    }
    glfwSetErrorCallback(
        [](int code, const char* err_str) {
            std::cout << "Callbeck error\n";
            throw std::runtime_error(err_str);
        }
    );

    glfwSetWindowSizeCallback(m_pWindow,
        [](GLFWwindow* pWindow, int width, int height)
        {
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

Window::Window(Window &&moved) noexcept
{
    glfwDestroyWindow(m_pWindow);

    m_pWindow = moved.m_pWindow;
    m_data.title = std::move(moved.m_data.title);
    m_data.width = moved.m_data.width;
    m_data.height = moved.m_data.height;
    m_data.custom_resize_function = moved.m_data.custom_resize_function;
    m_initialized = moved.m_initialized;
    error_msg = moved.error_msg;

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
    m_data.custom_resize_function = moved.m_data.custom_resize_function;
    m_initialized = moved.m_initialized;
    error_msg = moved.error_msg;

    ++m_glfwInitNum;

    moved.m_pWindow = nullptr;
    return *this;
}

void Window::update()
{
    if (!m_initialized)
        throw std::runtime_error(error_msg);
    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();
}

bool Window::is_active() const noexcept
{
    return m_pWindow != nullptr? !glfwWindowShouldClose(m_pWindow) : false;
}

int Window::getWidth() const noexcept
{
    return m_data.width;
}

int Window::getHeight() const noexcept
{
    return m_data.height;
}

void Window::destroy()
{
    glfwDestroyWindow(m_pWindow);
}

void Window::setResizeCallback(const resizeCallback& resizeFunction)
{
    m_data.custom_resize_function = resizeFunction;
}

Window::~Window()
{
    std::cout << "Window destructor\n";
    if (--m_glfwInitNum <= 0)
    {
        std::cout << "GLFW Terminate\n";
        glfwTerminate();
    }
}

}


