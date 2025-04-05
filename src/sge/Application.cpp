#include "sge/Application.hpp"

namespace sge {

Application::Application()
    : m_window("Sge app", 1000, 1000)
{
    std::cout << "Application Constructor\n";
}

Application::Application(const char* title)
    : m_window(title, 1000, 1000)
{
    std::cout << "Application Constructor\n";
}

Application::Application(Application &&moved) noexcept
    : m_window(std::move(moved.m_window))
{}

Application &Application::operator=(Application &&moved) noexcept
{
    if (&moved == this)
        return *this;

    m_window = std::move(moved.m_window);
    
    return *this;
}

void Application::start()
{

    while(m_window.is_active())
    {
        m_window.update();
        std::cout << m_window.getWidth() << '\n';
        onUpdate();
    }
    m_window.destroy();
}


Application::~Application()
{
    std::cout << "Application Destructor\n";
}

}
