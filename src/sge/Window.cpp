#include "Window.hpp"
#include <stdexcept>

#include <iostream>


namespace sge
{

Window::Window(std::string title, size_t width, size_t height) : m_data( {std::move(title), width, height} )
{
    std::cout << "Window constructor: " << m_data.title << '\n';

    glfwSetErrorCallback(
        [](int code, const char* err_str) {
            std::cout << "Callbeck error\n";
            throw std::runtime_error(err_str);
        }
    );

    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    glfwInit();
    ++m_glfwInitNum;

    try
    {
        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);
        
        glfwMakeContextCurrent(m_pWindow);

        setCallbacks();

    }
    catch(std::runtime_error& err)
    {
        if (--m_glfwInitNum <= 0)
        {
            std::cout << "GLFW Terminate\n";
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
    m_data.custom_resize_function = moved.m_data.custom_resize_function;
 
    ++m_glfwInitNum;

    moved.m_pWindow = nullptr;
    return *this;
}

void Window::update()
{
    if (m_isDestroy)
        throw std::runtime_error("Window update failure. Window is shutdown");

    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();
}

void Window::setCallbacks()
{
    glfwSetWindowUserPointer(m_pWindow, &m_data);

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

Window::~Window()
{
    std::cout << "Window destructor: " << m_data.title << '\n';
    shutdown();
    if (--m_glfwInitNum <= 0)
    {
        std::cout << "GLFW Terminate\n";
        glfwTerminate();
    }
}

}


