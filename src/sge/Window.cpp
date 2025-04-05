#include "Window.hpp"
#include <stdexcept>

#include <iostream>


namespace sge
{

Window::Window(std::string title, size_t width, size_t height) : m_title(title), m_width(width), m_height(height)
{
    std::cout << "Window constructor\n";

    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    if (glfwGetError(&error_msg))
        throw std::runtime_error(error_msg);

    glfwInit();
    if (glfwGetError(&error_msg))
        throw std::runtime_error(error_msg);
    ++m_glfwInitNum;

    m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_pWindow);
    
    if (!glfwGetError(&error_msg))
    { 
        m_initialized = true; 
    }
    glfwSetErrorCallback(errorCallback);
}

Window::Window(Window &&moved) noexcept
{
    m_pWindow = std::move(moved.m_pWindow);
    m_title = std::move(moved.m_title);
    m_width = std::move(moved.m_width);
    m_height = std::move(moved.m_height);
    bool m_initialized = std::move(moved.m_initialized);
}

Window &Window::operator=(Window &&moved) noexcept
{
    if (&moved != this)
    {
        m_pWindow = std::move(moved.m_pWindow);
        m_title = std::move(moved.m_title);
        m_width = std::move(moved.m_width);
        m_height = std::move(moved.m_height);
        bool m_initialized = std::move(moved.m_initialized);
    }
    return *this;
}

void Window::errorCallback(int code, const char* err_str)
{
    std::cout << "Callbeck error\n";
    throw std::runtime_error(err_str);
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
    return !glfwWindowShouldClose(m_pWindow);
}

int Window::getWidth()
{
    glfwGetFramebufferSize(m_pWindow, &m_width, &m_height);
    return m_width;
}

int Window::getHeight()
{
    glfwGetFramebufferSize(m_pWindow, &m_width, &m_height);
    return m_height;
}

void Window::destroy()
{
    glfwDestroyWindow(m_pWindow);
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


