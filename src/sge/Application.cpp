#include "sge/Application.hpp"

#include "sge/Logger.hpp"

namespace sge {

Application::Application()
    : m_window("Sge app", 1000, 1000)
{
    log::info("Application Constructor");
}

Application::Application(const char* title)
    : m_window(title, 1000, 1000)
{
    log::info("Application Constructor");

  
    m_window.setResizeCallback(
        [&](const windowSizeData& size_data)
        {
            log::data("Window size: %dx%d", size_data.width, size_data.height);
        }
    );
    m_window.setCursorCallback(
        [&](const cursorPos& cursor_pos)
        {
            log::data("Cursor: %f %f", cursor_pos.x, cursor_pos.y);
        }
    );
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
    log::info("App start");
    while(m_window.is_active())
    {
        log::data("App update");
        m_window.update();
        onUpdate();
    }
    m_window.shutdown();
}


Application::~Application()
{
    log::info("Application Destructor"); 
}

}
