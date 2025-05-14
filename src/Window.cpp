#include "Window.hpp"
#include "sge/Logger.hpp"

#include "sge/SGEexception.hpp"

namespace sge
{

Window::Window(std::string title, size_t width, size_t height) : m_data( {std::move(title), width, height} )
{
    log::info("Window constructor: %s", m_data.title.c_str());

    glfwSetErrorCallback(
        [](int code, const char* err_str) {
            throw errors::glfw_error(err_str);
        }
    );

    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    glfwInit();
    ++m_glfwInitNum;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    try
    {
        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);
        
        glfwMakeContextCurrent(m_pWindow);

        glfwSetWindowUserPointer(m_pWindow, &m_data);
        setResizeCallback();
        setCursorCallback();

    }
    catch(...)
    {
        if (--m_glfwInitNum <= 0)
        {
            log::info("GLFW Terminate");
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
        throw errors::glfw_error("Window update failure. Window is shutdown");

    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();
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
            if (data.custom_cursor_function)
            {
                cursorPos cursor_data{xpos, ypos};
                data.custom_cursor_function(cursor_data);
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

void Window::setCursorCallback(const cursorCallback& cursorFunction)
{
    m_data.custom_cursor_function = cursorFunction;
}

Window::~Window()
{
    log::info("Window destructor: %s", m_data.title.c_str());
    shutdown();
    if (--m_glfwInitNum <= 0)
    {
        log::info("GLFW Terminate");
        glfwTerminate();
    }
}

}


